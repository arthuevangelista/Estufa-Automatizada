Micro e Micro - 2.2017

# Ponto de Controle 01

Projeto de Automação com MSP430

> Controle hídrico (Controle do tempo de abertura das torneiras e chuveiros);

> Controle de irrigação do jardim/lavoura/plantação (Entrada de dados do usuário sobre as plantas, posição delas (ordenação na lista de elementos), temperatura ambiente e umidade ambiente);

> Controle com Relés, Válvula solenóide, Sensores de umidade, Sensores de temperatura, módulo Wifi, bluetooth;

> Média de temperatura e umidade, desvios padrões, estatísticas do ambiente e etc;

> Ver se tem como linkar com ASP.NET framework e Excel;

    Justificativa
        O controle hídrico em lavoures, jardins residenciais e estufas tem papel fundamental nas finanças de uma empresa ou residência. Estima-se que boa parte dos gastos com água potável são devido estas atividades. Em uma situação de crise hídrica como a atual e o preço da água se elevando a cada dia, uma empresa ou residência com controle de seus gastos hídricos obtém vantagem expressiva.

> Uso da opção de low-power mode do MSP430 pode oferecer vantagem nos momentos em que não estiver sendo utilizado;

> Relés e válvulas todas normalmente fechadas provê economia substancial de energia;

> Dúvida: Entrada de dados no sistema;

> Banco de dados ficaria armazenado em um dispositivo flash externo ao microcontrolador. Listas encadeadas podem ser uma boa abordagem para guardas elementos, adicionar/remover elementos e etc do banco de dados. CUIDADO! Listas são realizadas com alocação dinâmica de memória (pode dar problema na memória RAM do MSP430 se não for especificado que a lista deve estar na memo flash);
