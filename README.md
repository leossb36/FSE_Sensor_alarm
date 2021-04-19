# Sensor Alarm

## Alunos
|Matrícula | Aluno |
| -- | -- |
| 15/0135521  |  Leonardo dos Santos Silva Barreiros |

## Sobre
<p align="justify"> Projeto que tem por objetivo a implementação de um sistema distribuído de automação residencial,
a fim de realizar monitoramento e acionamento de sensores e dispositivos.
O sistema é desenvolvido na linguagem C e funciona em conjunto das placas Raspberry Pi além de realizar troca de dados
via socket, sendo este Full-duplex.

## Uso
<p align=justify> Para Utilizar o sistema primeiramente tenha instalado em sua maquina o gcc,
após isto é necessário que rode <strong>Primeiro</strong> o servidor central que esta na pasta central_server,
em seguida rode o servidor distribuido que encontra-se na pasta
distributed_server.

Para compilar o projeto digite:

```sh
$ make all
```

E executar:

```sh
$ make run
```

## Observação

As mensagens enviadas via sockets seguem o seguinte padrão:

```sh
 <evento>:<payload>
```
<p align="justify"> Onde evento descreve o tipo da mensagem e payload seu conteúdo. No processo de transmissão de dados, é feito o parser da estrutura da mensagem e assim as mensagem são tratadas de acordo com seus tipos evento.