#include <msp430.h>

/* =====================================================
 * DECLARAÇÃO DE CONSTANTES
 * -----------------------------------------------------*/

/* MODULO RELE -> SAÍDAS */
#define K1 BIT0 // K1 = P1.0
#define K2 BIT1 // K2 = P1.1
#define K3 BIT2 // K3 = P1.2
#define K4 BIT3 // K4 = P1.3

#define LED BIT6 // LED = P1.6

/* SENSORES -> ENTRADAS */
#define LDR BIT4 // LDR = P1.4
#define UMI BIT5 // UMI = P1.5
#define DHTPIN BIT7 // DHT11 = P1.7

/* =====================================================*/

/* =====================================================
 * VARIÁVEIS GLOBAIS / PROTÓTIPOS DE FUNÇÕES
 * -----------------------------------------------------*/

/* DHT 11 */
unsigned char volatile TOUT;
unsigned char volatile SECOND_TIMER=0;

unsigned char data[5];

void acorda(void);
unsigned char resposta(void);
unsigned char lerByte(void);
unsigned char lerPacket(unsigned char *);
unsigned char checkParidade(unsigned char *);

/* =====================================================*/

#pragma vector = TIMER0_A0_VECTOR
__interrupt void CCR0_ISR(void){
        SECOND_TIMER++;
        TOUT=1;
        TACCTL0 &= ~(CCIFG);
}

/* =====================================================
 * PROGRAMA PRINCIPAL
 * -----------------------------------------------------*/
void main(void){
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer

    /* DECLARA ENTRADAS E SAÍDAS */
    P1DIR |= K1 + K2 + K3 + K4; // Demais pinos são entradas
    P1OUT |= (K1 + + K2 + K3 + K4); // Todos os pinos setados => Módulo relé é ativo em BAIXA

    P1REN |= (UMI + DHTPIN);       // Habilita o resistor de pull-up/down nas entradas digitais
    P1OUT |= (UMI + DHTPIN);       // UMI e DHT11 ficam como pull-up;


    BCSCTL1 = CALBC1_1MHZ;      // Seta SMCLK to 1MHz
    DCOCTL = CALDCO_1MHZ;       // Seta SMCLK to 1MHz

    TACCR0 = 50000;             // timer A contando 5Hz
    TACCTL0 = CCIE;             //Enable na interrupção
    TA0CTL = TASSEL_2 + ID_2 + MC_1 + TACLR;    // SMCLK, divisor por 4, up mode,

    _enable_interrupt();        // Permite GIE

    __BIS_SR(LPM0_bits);    // Entra no modo de economia de energia

    while(1){

        /* INTERFACE COM DHT11 */
        if(SECOND_TIMER >= 20){
            __BIS_SR(LPM0_exit);
            acorda();
            if(checkParidade()){
                data[0] = read_Byte(); // Umidade byte 1
                data[1] = read_Byte(); // Umidade byte 2
                data[2] = read_Byte(); // Temperatura byte 1
                data[3] = read_Byte(); // Temperatura byte 2
                data[4] = read_Byte(); // byte de paridade
            }

            if (checkParidade(data)){
                P1OUT |= LED;          // Liga LED da P1.6 certificando que a paridade está correta
            }else{
                P1OUT &= ~(LED);       // Desliga P1.6 caso contrário
                break;                 // Quebra loop infinito e vai pra próxima iteração
            }

            TACTL |= TACLR;
            TA0CTL |= 0x10;
            TACCR0 = 50000;   // Manda pra 5Hz novamente
            SECOND_TIMER = 0; // zera contador entre-leituras
            /* fim da interface com o DHT11 */

        if(data[2] >= 0x10){            // Se temperatura acima de 16ºC, resfria
            P1OUT ^= (K2 + K3);
        }else{
            if(data[2] <= 0x16){        // Se temperatura abaixo de 25ºC, esquenta
                P1OUT ^= (K2 + K3);
            }
        } /* fim do if-else*/

        P1OUT &= ~K1; // LED sempre ligado por enquanto

      // SUB-ROTINA ASSEMBLY
        __asm__("bis.b   #8, &__P1OUT \n"  // Seta o pino de saída P1.3 = K4 (0x08 = 0000 1000)
                "mov.b   &__P1IN, R15 \n"  // Move entrada P1IN para reg temporário
                "and.b   #10, R15 \n"      // Compara (0x10 = 0001 0000) com R15 (P1IN = P1.4)
                "jz  umidadeBaixa \n"      // Se for P1.4 = 0, então jump para umidadeBaixa
                "jmp fim \n"               // Jump caso contrário

                "umidadeBaixa: \n"
                "and.b   #F7, &__P1OUT \n" // Reseta o pino de saída P1.3 = K4 (0xF7 = 1111 0111) RELÉ ATIVO EM BAIXA
                "mov.b   #FF, R14 \n" // Adiciona o valor 0xFF no reg R14 para contagem
                "mov.b   #FF, R13 \n"
                "mov.b   #3F, R12 \n" // Conta até 2^23 ~= 5 segundos
                "jmp contagem0 \n"

                "contagem0: \n" // sub-rotina de contagem (MCLK a 1MHz)
                "sub.b   #1, R14 \n" // Cada jump => 2 ciclos de clock
                "jz contagem1 \n" // Cada decremento => 1 ciclo de clock
                "jmp contagem0 \n"

                "contagem1: \n"
                "sub.b   #1, R13 \n"
                "jz contagem2 \n"
                "mov.b   #FF, R14 \n"
                "jmp contagem0 \n"

                "contagem2: \n"
                "sub.b   #1, R12 \n"
                "jz fim \n"
                "mov.b   #FF, R14 \n"
                "mov.b   #FF, R13 \n"
                "jmp contagem0 \n"

                "fim: \n"
                "clr.b   R15 \n"
                "clr.b   R14 \n"
                "clr.b   R13 \n"
                "clr.b   R12 \n");

        }/* fim do if-else (second timer) */
    } /* fim do while */
} /* FIM DO PROGRAMA PRINCIPAL */


/* =====================================================
 * FUNÇÕES DO DHT11
 * ----------------------------------------------------- */
unsigned char lerByte(){
    TOUT = 0;
    unsigned char numero = 0;
    unsigned char i;
    TACCTL0 &= ~(CCIE);              // Limpa TACCTL
    for (i=8; i>0; i--){            // Lê os bits enviados pelo DHT11 do LSB para o MSB
        while(!(P1IN & DHTPIN));
        TACTL |= TACLR;
        TA0CTL |= 0x10;
        TACCTL0 |= CCIE;
        while((P1IN & DHTPIN));
        TA0CTL &= ~(0x30);
        if (TAR > 13)
            numero |= 1 << (i-1);
    }
    return numero;
} /* fim lerByte */

unsigned char resposta(){
    TOUT=0;
    TACTL |= TACLR;
    TACCR0 = 25;
    TACCTL0 |= CCIE;
    while(!(P1IN & DHTPIN) && !TOUT);
    if (TOUT)
        return 0;
    else {
        TACTL |= TACLR;
        TACCTL0 |= CCIE;
        while((P1IN & DHTPIN) && !TOUT);
        if(TOUT)
            return 0;
        else{
            TACCTL0 &= ~(CCIE);
            return 1;
        }
    } /* fim do if-else */
} /* fim resposta */

void acorda(){
    P1DIR |= DHTPIN;        // Seta o pino do DHT11 para OUTPUT
    P1OUT &= ~(DHTPIN);     // Dá clear no pino do DHT11
    __delay_cycles(25000);
    P1OUT |= DHTPIN;        // Depois do delay, seta o pino
    __delay_cycles(30);
    P1DIR &= ~(DHTPIN);     // Clear no pino do DHT11 para INPUT
} /* fim acorda*/

unsigned char checkParidade(unsigned char *data){               // Apenas checa se há o byte de paridade e é equivalente à soma dos outros bytes
    if (data[4] != (data[0] + data[1] + data[2] + data[3])){    // Caso seja, retorna 1 dizendo que não houve problemas
        return 0;
    }
    else return 1;                                              // Caso haja um problema, retorna 0 e manda reiniciar a leitura
} /* fim check Paridade*/
