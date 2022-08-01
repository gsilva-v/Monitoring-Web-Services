# Monitoramento de serviços Web

# Sobre

## O que é um Monitor de Serviços Web?
 O Monitoramento de Serviço Web funciona emulando as ações de um usuário real. Ele pesquisa e testa regularmente os serviços da Internet para verificar seu status e desempenho.

### E para que serve?
- É possível avaliar o desempenho dos seus websites e controlar a sua nuvem e (outros) serviços.
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
Siga os proximos passos para fazer uso da ferramenta: 
## Como instalar
Antes, você deve garantir que as bibliotecas necessárias estão instaladas no seu ambiente:

- [Libcurl](https://curl.se/libcurl/)

Em seu terminal, clone este repositório:
```bash
git clone https://github.com/42sp/42labs-selection-process-v2-gsilva-v WebServiceMonitor
```
Após a conclusão execute:
```bash
cd WebServiceMonitor && make build
```
Ao fim da compilação, o monitor estará pronto para ser usado.

## Como criar um arquivo de configuração
Na pasta `/conf` deste repositório, crie um arquivo com a extensão `.db`, nele coloque as configurações dos serviços que deseja monitorar.
Esse arquivo de configuração deve seguir os seguintes padrões:

- Cada linha deve conter um serviço a ser monitorado.

- Os itens da linha devem estar em ordem (apelido do serviço, protocólo, endereço) e separados por tabulações entre eles.
	
	- Para monitoramento por protocólo HTTP, deve-se colocar mais 3 configurações: Método HTTP, status de response esperado e intervalo entre os testes (em segundos). Também separados por tabulações.

	- Para monitoramento por PING, deve-se colocar apenas o intervalo ao final da linha.

	- Para monitoramento po DNS deve-se colocar o intervalo e o servidor DNS no final da linha.


Exemplo de linha de configuração: 
```bash 
HTTP :
intra	HTTP	intra.42.fr	GET	301	10

PING :
game ping test	PING	game.42sp.org.br	20

DNS :
google	DNS	google.com	30	8.8.8.8
```

## Como usar a ferramenta
Após a compilação e criação do seu arquivo de configuração, execute em seu terminal:
```./monitoring ./conf/{seu_arquivo}```

O programa deve começar a ser executado logo em seguida, mostrando os status dos monitorados.

Também podemos usar com flags: 
 - `--simplify ou -s` irá simplificar o log gerado.
 - `--pretty` irá deixar o log com uma aparencia mais agradável.
 - `--help` irá mostrar como passar os argumentos corretamente para a execução.
 - `--http=[yes/no]` irá ativar ou desativar o monitoramento para o protocólo HTTP
 - `--ping=[yes/no]` irá ativar ou desativar o monitoramento para o protocólo PING
 - `--dns=[yes/no]` irá ativar ou desativar o monitoramento para o protocólo DNS

#
# Resultados

## Sobre o log que é gerado

O log que aparece no terminal contém informações como: nome do monitorado, url requisitada, resultado esperado, resultado do ultimo teste.

Para simplificar esse log, você pode usar a flag `--simplify`. Com a flag ativada, o log sera reduzido a apenas: nome do monitorado, resultado to ultimo teste.

### Quais sinais deve receber mais atenção
Caso apareça algum log negativo, ele sera jogado para um arquivo que se encontra em `/logs/errors.log`, nesse arquivo terá, com mais profundidade qual o problema ocorrido sobre o monitorado.

#
# Bibliografia
- [IBM Internet Service Monitoring](https://www.ibm.com/docs/en/capm?topic=interface-available-internet-service-monitoring-monitors)

- [Ping Explaination](https://www.cloudradar.io/blog/web-monitoring-ping-vs-tcp-vs-http-checks)

- [LibCurl Explaination](https://curl.se/libcurl/)