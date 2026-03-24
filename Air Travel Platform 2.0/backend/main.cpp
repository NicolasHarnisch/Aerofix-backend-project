#include <iostream>
#include <string>
#include <vector>
#include "httplib.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

string reserva[10][6];

void inicializarPoltronas() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            reserva[i][j] = ""; 
        }
    }
}

bool poltronaValida(char poltrona, int classe) {
    if (classe == 1) return poltrona >= 'B' && poltrona <= 'E';
    return poltrona >= 'A' && poltrona <= 'F';
}

int main() {
    inicializarPoltronas();
    httplib::Server svr;

    cout << "Iniciando servidor Aerofix Backend na porta 8080..." << endl;

    svr.Options(R"(.*)", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.status = 200;
    });

    svr.Get("/assentos", [](const httplib::Request& req, httplib::Response& res) {
        json mapaAssentos = json::array();
        for (int i = 0; i < 10; i++) {
            json fileira = json::array();
            for (int j = 0; j < 6; j++) {
                json assento;
                assento["id"] = string(1, 'A' + j) + to_string(i + 1);
                assento["status"] = reserva[i][j].empty() ? "O" : "X";
                assento["ocupante"] = reserva[i][j]; 
                fileira.push_back(assento);
            }
            mapaAssentos.push_back(fileira);
        }
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(mapaAssentos.dump(), "application/json");
    });

    // ROTA INDIVIDUAL
    svr.Post("/reservar/individual", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        json resposta;
        try {
            auto body = json::parse(req.body);
            int classe = body["classe"];
            bool simular = body.contains("simular") ? (bool)body["simular"] : false;
            bool querRecomendacao = body.contains("recomendacao") ? (bool)body["recomendacao"] : false;
            string nome = body.contains("nome") ? string(body["nome"]) : "Passageiro";

            if (querRecomendacao) {
                bool pertoJanela = body.contains("pertoJanela") ? (bool)body["pertoJanela"] : false;
                bool encontrou = false;
                
                for (int f = 0; f < 10 && !encontrou; f++) {
                    for (int c = 0; c < 6 && !encontrou; c++) {
                        if (reserva[f][c].empty()) {
                            if (classe == 2 && ((pertoJanela && (c == 0 || c == 5)) || (!pertoJanela && (c >= 1 && c <= 4)))) {
                                if(!simular) reserva[f][c] = nome;
                                resposta["sucesso"] = true; resposta["assentos"] = json::array({string(1, 'A' + c) + to_string(f + 1)}); encontrou = true;
                            } else if (classe == 1 && (c >= 1 && c <= 4)) {
                                if(!simular) reserva[f][c] = nome;
                                resposta["sucesso"] = true; resposta["assentos"] = json::array({string(1, 'A' + c) + to_string(f + 1)}); encontrou = true;
                            }
                        }
                    }
                }
                if (!encontrou) { resposta["sucesso"] = false; resposta["erro"] = "Nenhuma poltrona disponivel."; res.status = 404; }
            } else {
                int fileira = body["fileira"];
                char coluna = toupper(string(body["coluna"])[0]);
                if (!poltronaValida(coluna, classe)) {
                    resposta["sucesso"] = false; resposta["erro"] = "Poltrona invalida."; res.status = 400;
                } else if (!reserva[fileira - 1][coluna - 'A'].empty()) {
                    resposta["sucesso"] = false; resposta["erro"] = "Poltrona ja reservada."; res.status = 409;
                } else {
                    if(!simular) reserva[fileira - 1][coluna - 'A'] = nome;
                    resposta["sucesso"] = true;
                }
            }
        } catch (...) { resposta["erro"] = "JSON invalido."; res.status = 400; }
        res.set_content(resposta.dump(), "application/json");
    });

    // ROTA FAMÍLIA (Agora com garantia de janela na Executiva)
    svr.Post("/reservar/familia", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        json resposta;
        try {
            auto body = json::parse(req.body);
            int classe = body["classe"];
            int numPessoas = body["numPessoas"];
            bool simular = body.contains("simular") ? (bool)body["simular"] : false;
            vector<string> n = body.contains("nomes") ? body["nomes"].get<vector<string>>() : vector<string>(5, "Família");

            bool reservado = false;
            json assentos = json::array();

            for (int l = 0; l < 10 && !reservado; l++) {
                if (classe == 1) { // ====== ECONÔMICA (Sem janela) ======
                    if (numPessoas == 3 && reserva[l][1].empty() && reserva[l][2].empty() && reserva[l][3].empty()) {
                        if(!simular){ reserva[l][1]=n[0]; reserva[l][2]=n[1]; reserva[l][3]=n[2]; }
                        assentos = {"B" + to_string(l+1), "C" + to_string(l+1), "D" + to_string(l+1)}; reservado = true;
                    } 
                    else if (numPessoas == 4 && reserva[l][1].empty() && reserva[l][2].empty() && reserva[l][3].empty() && reserva[l][4].empty()) {
                        if(!simular){ reserva[l][1]=n[0]; reserva[l][2]=n[1]; reserva[l][3]=n[2]; reserva[l][4]=n[3]; }
                        assentos = {"B" + to_string(l+1), "C" + to_string(l+1), "D" + to_string(l+1), "E" + to_string(l+1)}; reservado = true;
                    }
                    else if (numPessoas == 5 && reserva[l][1].empty() && reserva[l][2].empty() && reserva[l][3].empty() && reserva[l][4].empty() && l+1 < 10 && reserva[l+1][2].empty()) {
                        if(!simular){ reserva[l][1]=n[0]; reserva[l][2]=n[1]; reserva[l][3]=n[2]; reserva[l][4]=n[3]; reserva[l+1][2]=n[4]; }
                        assentos = {"B" + to_string(l+1), "C" + to_string(l+1), "D" + to_string(l+1), "E" + to_string(l+1), "C" + to_string(l+2)}; reservado = true;
                    }
                } 
                else if (classe == 2) { // ====== EXECUTIVA (Garante Janela A ou F) ======
                    // 3 Pessoas
                    if (numPessoas == 3 && reserva[l][0].empty() && reserva[l][1].empty() && reserva[l][2].empty()) {
                        if(!simular){ reserva[l][0]=n[0]; reserva[l][1]=n[1]; reserva[l][2]=n[2]; }
                        assentos = {"A" + to_string(l+1), "B" + to_string(l+1), "C" + to_string(l+1)}; reservado = true;
                    }
                    else if (numPessoas == 3 && reserva[l][3].empty() && reserva[l][4].empty() && reserva[l][5].empty()) {
                        if(!simular){ reserva[l][3]=n[0]; reserva[l][4]=n[1]; reserva[l][5]=n[2]; }
                        assentos = {"D" + to_string(l+1), "E" + to_string(l+1), "F" + to_string(l+1)}; reservado = true;
                    }
                    // 4 Pessoas (CORRIGIDO: Agora sempre pega a Janela A ou F)
                    else if (numPessoas == 4 && reserva[l][0].empty() && reserva[l][1].empty() && reserva[l][2].empty() && reserva[l][3].empty()) {
                        if(!simular){ reserva[l][0]=n[0]; reserva[l][1]=n[1]; reserva[l][2]=n[2]; reserva[l][3]=n[3]; }
                        assentos = {"A" + to_string(l+1), "B" + to_string(l+1), "C" + to_string(l+1), "D" + to_string(l+1)}; reservado = true;
                    }
                    else if (numPessoas == 4 && reserva[l][2].empty() && reserva[l][3].empty() && reserva[l][4].empty() && reserva[l][5].empty()) {
                        if(!simular){ reserva[l][2]=n[0]; reserva[l][3]=n[1]; reserva[l][4]=n[2]; reserva[l][5]=n[3]; }
                        assentos = {"C" + to_string(l+1), "D" + to_string(l+1), "E" + to_string(l+1), "F" + to_string(l+1)}; reservado = true;
                    }
                    // 5 Pessoas
                    else if (numPessoas == 5 && reserva[l][0].empty() && reserva[l][1].empty() && reserva[l][2].empty() && reserva[l][3].empty() && reserva[l][4].empty()) {
                        if(!simular){ reserva[l][0]=n[0]; reserva[l][1]=n[1]; reserva[l][2]=n[2]; reserva[l][3]=n[3]; reserva[l][4]=n[4]; }
                        assentos = {"A" + to_string(l+1), "B" + to_string(l+1), "C" + to_string(l+1), "D" + to_string(l+1), "E" + to_string(l+1)}; reservado = true;
                    }
                    else if (numPessoas == 5 && reserva[l][1].empty() && reserva[l][2].empty() && reserva[l][3].empty() && reserva[l][4].empty() && reserva[l][5].empty()) {
                        if(!simular){ reserva[l][1]=n[0]; reserva[l][2]=n[1]; reserva[l][3]=n[2]; reserva[l][4]=n[3]; reserva[l][5]=n[4]; }
                        assentos = {"B" + to_string(l+1), "C" + to_string(l+1), "D" + to_string(l+1), "E" + to_string(l+1), "F" + to_string(l+1)}; reservado = true;
                    }
                }
            }

            if (reservado) { resposta["sucesso"] = true; resposta["assentos"] = assentos; } 
            else { resposta["sucesso"] = false; resposta["erro"] = "Sem poltronas adjacentes suficientes."; res.status = 404; }
        } catch (...) { res.status = 400; }
        res.set_content(resposta.dump(), "application/json");
    });

    // ROTA CASAL
    svr.Post("/reservar/casal", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        json resposta;
        try {
            auto body = json::parse(req.body);
            int escolha = body["escolhaProximidade"]; 
            bool simular = body.contains("simular") ? (bool)body["simular"] : false;
            vector<string> n = body.contains("nomes") ? body["nomes"].get<vector<string>>() : vector<string>(2, "Casal");
            
            bool reservado = false; json assentos = json::array();

            if (escolha == 1) { // Separados na Janela
                int achados = 0;
                for (int i = 0; i < 2; i++) {
                    char f = (i == 0) ? 'A' : 'F';
                    for (int l = 0; l < 10; l++) {
                        if (reserva[l][f - 'A'].empty()) {
                            if(!simular) reserva[l][f - 'A'] = n[i];
                            assentos.push_back(string(1, f) + to_string(l+1));
                            achados++; break;
                        }
                    }
                }
                if(achados == 2) reservado = true;
            } 
            else if (escolha == 2) { // Juntos perto da Janela
                for (int l = 0; l < 10 && !reservado; l++) {
                    if (reserva[l][0].empty() && reserva[l][1].empty()) {
                        if(!simular){ reserva[l][0]=n[0]; reserva[l][1]=n[1]; }
                        assentos = {"A" + to_string(l+1), "B" + to_string(l+1)}; reservado = true;
                    } else if (reserva[l][5].empty() && reserva[l][4].empty()) {
                        if(!simular){ reserva[l][5]=n[0]; reserva[l][4]=n[1]; }
                        assentos = {"F" + to_string(l+1), "E" + to_string(l+1)}; reservado = true;
                    }
                }
            }
            else if (escolha == 3) { // Juntos longe da Janela
                for (int l = 0; l < 10 && !reservado; l++) {
                    for (int c = 1; c < 4; c++) {
                        if (reserva[l][c].empty() && reserva[l][c+1].empty()) {
                            if(!simular){ reserva[l][c]=n[0]; reserva[l][c+1]=n[1]; }
                            assentos = {string(1, 'A'+c) + to_string(l+1), string(1, 'A'+c+1) + to_string(l+1)}; 
                            reservado = true; break;
                        }
                    }
                }
            }

            if (reservado) { resposta["sucesso"] = true; resposta["assentos"] = assentos; } 
            else { resposta["sucesso"] = false; resposta["erro"] = "Poltronas indisponíveis."; res.status = 404; }
        } catch (...) { res.status = 400; }
        res.set_content(resposta.dump(), "application/json");
    });

// Configuração de porta dinâmica para servidores na nuvem (Render, AWS, etc)
    const char* port_str = getenv("PORT");
    int port = port_str ? stoi(port_str) : 8080;
    
    cout << "Servidor Aerofix rodando na porta " << port << "..." << endl;
    svr.listen("0.0.0.0", port);
    
    return 0;
}