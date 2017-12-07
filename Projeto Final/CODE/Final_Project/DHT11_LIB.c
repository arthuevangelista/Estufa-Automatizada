#include <msp430.h>
#include <DHT11_LIB.h>

unsigned char read_Byte(){
    TOUT = 0;
    unsigned char num = 0;
    unsigned char i;
    CLR(TACCTL0,CCIE);
    for (i=8; i>0; i--){
        while(!(TST(P2IN,DPIN)));
        SET(TACTL,TACLR);
        SET(TA0CTL,0x10);
        SET(TACCTL0,CCIE);
        while(TST(P2IN,DPIN));
        CLR(TA0CTL,0x30);
        if (TAR > 13)
            num |= 1 << (i-1);
    }
    return num;
}

unsigned char read_Packet(unsigned char * data){
    start_Signal();
    if (check_Response()){
        data[0] = read_Byte();
        data[1] = read_Byte();
        data[2] = read_Byte();
        data[3] = read_Byte();
        data[4] = read_Byte();
        return 1;
    }
    else return 0;
}

unsigned char check_Response(){
    TOUT=0;
    SET(TACTL,TACLR);
    TACCR0 = 25;
    SET(TACCTL0,CCIE);
    while(!(TST(P2IN,DPIN)) && !TOUT);
    if (TOUT)
        return 0;
    else {
        SET(TACTL,TACLR);
        SET(TACCTL0,CCIE);
        while((TST(P2IN,DPIN)) && !TOUT);
        if(TOUT)
            return 0;
        else{
            CLR(TACCTL0,CCIE);
            return 1;
        }
    }
}

void start_Signal(){
    SET(P2DIR, DPIN);
    CLR(P2OUT,DPIN);
    __delay_cycles(25000);
    SET(P2OUT,DPIN);
    __delay_cycles(30);
    CLR(P2DIR,DPIN);
}

unsigned char check_Checksum(unsigned char *data){
    if (data[4] != (data[0] + data[1] + data[2] + data[3])){
        return 0;
    }
    else return 1;
}
