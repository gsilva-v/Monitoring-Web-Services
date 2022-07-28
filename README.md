# Monitoramento de serviços Web

# Sobre

## O que é um Monitor de Serviços Web?
 O Monitoramento de Serviço Web funciona emulando as ações de um usuário real. Ele pesquisa e testa regularmente os serviços da Internet para verificar seu status e desempenho.


### E para que serve?
-  É possível avaliar o desempenho dos seus websites e controlar a sua nuvem e (outros) serviços.
- Uma ferramenta de monitoramento pode ser usada para executar um teste de ping. O ping indica se é possível conectar-se ao seu website.
- O monitoramento de serviços de Internet também ajuda a reduzir o tempo de inatividade (ou seja, impedir panes nos seus servidores).

## Como é o seu funcionamento:
Basicamente é feito requisições ao monitorados e tento uma resposta que já esta configurada como esperada, que seja comparada com a recebida para verificar se o serviço está dentro do padrão. 

### Funcionamento por HTTP :
Os monitores HTTP e HTTPS verificam a disponibilidade e o tempo de resposta dos servidores web. Use o monitor HTTP nas seguintes situações:
- O site de destino é estático.
- O site de destino é servido pelo protocolo HTTP.
- Para realizar o monitoramento em várias plataformas.
- Onde a velocidade é um fator determinante (o monitor HTTP oferece alto desempenho)

### Funcionamento por PING :
Uma verificação de ping é uma verificação básica de nível de rede. O ping usa o protocolo ICMP para verificar a acessibilidade da rede do site/dispositivo de rede que você está verificando. Isso informa que o dispositivo está disponível e conectado à interface de rede. No entanto, apenas porque algo retorna um ping, não é certo que o serviço no dispositivo esteja em execução, mas ajuda na solução de problemas. Então, definitivamente, uma das principais verificações a serem usadas.


### Funcionamento por DNS :
O monitor DNS usa o serviço DNS (Domain Name System) para localizar informações sobre um ou mais hosts.

O monitor DNS usa o endereço IP do host para pesquisar o nome do host ou o nome do host para pesquisar o endereço IP. O monitor mede o desempenho do serviço registrando o resultado da pesquisa e os tempos de resposta. O monitor também registra detalhes sobre cada consulta enviada ao servidor.
#
# Instalação e Funcionamento

## Como instalar

## Como usar a ferramenta

#
# Resultados

## Sobre o log que é gerado

### Como ler o log

### Quais sinais deve receber mais atenção


#
# Bibliografia
- [IBM Internet Service Monitoring](https://www.ibm.com/docs/en/capm?topic=interface-available-internet-service-monitoring-monitors)

- [Ping Explaination](https://www.cloudradar.io/blog/web-monitoring-ping-vs-tcp-vs-http-checks)