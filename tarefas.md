[] modificar o nome das funções de limpeza _ListeningSocket na poll
[] entender o pq da linha:
    size_t firstLineEnd = request.find("\r\n");//verificar depois o motivo disso
    no Request.cpp

[] melhor o codigo void Request::_parseQuery()

[] mudar o nome do "std::vector<int> getSizeServers();" em Data e WebServ


===========================================

# checklist

[x] Seu programa precisa usar um arquivo de configuração como argumento ou usar um caminho padrão.

[?] You can’t execve another web server / Você não pode "execve" outro servidor web.

[?] Seu servidor nunca deve bloquear e o cliente pode ser devolvido corretamente, se necessário.

[x] Deve ser não bloqueador e usar apenas 1 poll() (ou equivalente) para todas as operações de I/O entre o cliente e o servidor (escuta incluída).

[?] poll() (ou equivalente) deve verificar a leitura e a gravação ao mesmo tempo.

[x] Você nunca deve fazer uma operação de leitura ou gravação sem passar por poll() (ou equivalente).

[x] A verificação do valor de errno é estritamente proibida após uma operação de leitura ou escrita.

[x] Você não precisa usar poll() (ou equivalente) antes de ler seu arquivo de configuração.

[?] Assim, se você tentar read/recv ou write/send qualquer descritor de arquivo sem
usar poll() (ou equivalente), sua nota será 0

[x]  Você pode usar qualquer macro e definir como FD_SET, FD_CLR, FD_ISSET, FD_ZERO (entender o que e como eles fazem isso é muito útil).

[?] Uma solicitação ao seu servidor nunca deve ficar suspensa para sempre.

[?] Seu servidor deve ser compatível com o navegador de sua escolha.

[?] Consideraremos que o NGINX é compatível com HTTP 1.1 e pode ser usado para comparar cabeçalhos e comportamentos de resposta.

[?] Seus códigos de status de resposta HTTP devem ser precisos.

[?] Seu servidor deverá ter páginas de erro padrão se nenhuma for fornecida.

[x] Você não pode usar fork para algo diferente de CGI (como PHP, ou Python, e assim por diante).

[x] Você deve ser capaz de servir um site totalmente estático.

[ ] Os clientes devem ser capazes de fazer upload de arquivos.

[ ] Você precisa de pelo menos os métodos GET, POST e DELETE.

[ ] Testes de estresse em seu servidor. Deve permanecer disponível a todo custo.

[x] Seu servidor deve ser capaz de escutar múltiplas portas (consulte Arquivo de configuração).

## Arquivo de Configuração

[ ] Escolha a porta e o host de cada 'servidor'.

[ ] Configure os server_names ou não

[ ] O primeiro servidor para um host:port será o padrão para este host:port (isso significa que ele responderá a todas as solicitações que não pertencem a outro servidor)

[x] Configurar páginas de erro padrão.

[ ] Limite o tamanho do corpo do cliente.

[ ]  Configure rotas com uma ou várias das seguintes regras/configuração (as rotas não serão estar usando regexp):

    [ ] Defina uma lista de métodos HTTP aceitos para a rota.

    [ ] Defina um redirecionamento HTTP.

    [x]  Defina um diretório ou arquivo de onde o arquivo deve ser pesquisado (por exemplo, se url  /kapouet tiver raiz em /tmp/www, url /kapouet/pouic/toto/pouet for /tmp/www/pouic/toto/pouet ).

    [x] Ative ou desative a listagem de diretórios.

    [x] Defina um arquivo padrão para responder se a solicitação for um diretório.

    [ ] Execute CGI com base em determinada extensão de arquivo (por exemplo .php).

    [ ] Faça funcionar com métodos POST e GET.

    [ ] Torne a rota capaz de aceitar arquivos carregados e configure onde eles devem ser salvo

        [ ] Você quer saber o que é um CGI é

        [ ] Como você não chamará o CGI diretamente, use o caminho completo como PATH_INFO.

        [ ] Apenas lembre-se que, para solicitações em pedaços, seu servidor precisa descompactá-las, o CGI esperará EOF como final do corpo.

        [ ] A mesma coisa para a saída do CGI. Se nenhum content_length for retornado do CGI, EOF marcará o final dos dados retornados.
        
        [ ] Seu programa deverá chamar o CGI com o arquivo solicitado como primeiro argumento.

        [ ] O CGI deve ser executado no diretório correto para acesso ao arquivo de caminho relativo

        [ ] Seu servidor deve funcionar com um CGI (php-CGI, Python e assim por diante).

[ ]Você deve fornecer alguns arquivos de configuração e arquivos básicos padrão para testar e demonstrar que cada recurso funciona durante a avaliação 