# Usa uma imagem oficial do Linux com o compilador C++ (GCC) já instalado
FROM gcc:latest

# Cria a pasta de trabalho dentro do servidor
WORKDIR /usr/src/app

# Copia todos os arquivos da sua pasta backend para o servidor
COPY . .

# Compila o código C++ para Linux (Note que usa -lpthread em vez de -lws2_32)
RUN g++ main.cpp -o aerofix_api -lpthread

# Executa o sistema
CMD ["./aerofix_api"]