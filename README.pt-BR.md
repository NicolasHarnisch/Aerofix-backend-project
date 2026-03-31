# Aerofix - Sistema de Reserva de Assentos em Voos ✈️

> **Motor Leve de Alocação de Assentos** — Backend REST API em C++ com frontend vanilla JavaScript para reserva inteligente de assentos de avião

<div style="display: inline-block; margin-bottom: 15px;">
  <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++" />
  <img src="https://img.shields.io/badge/HTTPLib-FF6B6B?style=for-the-badge&logo=server&logoColor=white" alt="HTTPLib" />
  <img src="https://img.shields.io/badge/HTML5-E34F26?style=for-the-badge&logo=html5&logoColor=white" alt="HTML5" />
  <img src="https://img.shields.io/badge/CSS3-1572B6?style=for-the-badge&logo=css3&logoColor=white" alt="CSS3" />
  <img src="https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black" alt="JavaScript" />
  <img src="https://img.shields.io/badge/REST_API-FF6C37?style=for-the-badge&logo=rest&logoColor=white" alt="REST API" />
</div>

**Aerofix** é um sistema leve de reserva de assentos em voos com algoritmos inteligentes de alocação para reservas individuais, casais e famílias. Construído com **backend em C++** (httplib header-only) e **frontend vanilla JavaScript**.

Perfeito para demonstrar design de API REST, pensamento algorítmico e arquitetura cliente-servidor sem dependências de frameworks.

> 📚 **Documentação:** [🇺🇸 English](README.md) | 🇧🇷 Português (este arquivo)

---

## 📋 Índice

- [Aerofix - Sistema de Reserva de Assentos em Voos ✈️](#aerofix---sistema-de-reserva-de-assentos-em-voos-️)
  - [📋 Índice](#-índice)
  - [🎯 Visão Geral](#-visão-geral)
  - [🏗️ Arquitetura](#️-arquitetura)
  - [🛠️ Tecnologias \& Stack](#️-tecnologias--stack)
  - [📁 Estrutura de Pastas](#-estrutura-de-pastas)
  - [🚀 Instalação](#-instalação)
    - [Pré-requisitos](#pré-requisitos)
      - [Windows (MinGW)](#windows-mingw)
      - [Linux](#linux)
      - [macOS](#macos)
  - [🔨 Compilação \& Execução](#-compilação--execução)
    - [Backend](#backend)
    - [Frontend](#frontend)
    - [Testar API](#testar-api)
  - [📡 Endpoints da API REST](#-endpoints-da-api-rest)
    - [GET /assentos](#get-assentos)
    - [POST /reservar/individual](#post-reservarindividual)
    - [POST /reservar/familia](#post-reservarfamilia)
    - [POST /reservar/casal](#post-reservarcasal)
  - [✨ Funcionalidades \& Algoritmos](#-funcionalidades--algoritmos)
    - [Individual  ✈️](#individual--️)
    - [Família 👨‍👩‍👧‍👦](#família-)
    - [Casal 💑](#casal-)
    - [Motor de Recomendação](#motor-de-recomendação)
  - [🎫 Restrições de Classe](#-restrições-de-classe)
  - [🛫 Fluxo de Reserva](#-fluxo-de-reserva)
  - [🤝 Como Contribuir](#-como-contribuir)
  - [🗺️ Roadmap](#️-roadmap)
  - [👨‍💻 Autor](#-autor)

---

## 🎯 Visão Geral

Aerofix apresenta:

✅ **Alocação Inteligente** — Algoritmos dinâmicos para reservas individuais, casais e famílias  
✅ **Duas Classes** — Econômica (assentos restritos) e Executiva (todos os assentos)  
✅ **Atualizações em Tempo Real** — Gerenciamento de assentos em memória com disponibilidade instantânea  
✅ **Auto-Recomendação** — Sugestões inteligentes de assentos com modo simulação  
✅ **API RESTful** — Endpoints limpos com comunicação JSON  
✅ **Sem Frameworks** — C++ puro, JavaScript vanilla e HTML5  
✅ **CORS Habilitado** — Suporte completo para requisições cross-origin  

---

## 🏗️ Arquitetura

```
Frontend                      Backend
(JavaScript/HTML5)           (C++ + httplib)
     ↓                            ↓
  index.html         →  GET /assentos
  script.js          →  POST /reservar/individual
  style.css          →  POST /reservar/familia
                     →  POST /reservar/casal
                     ↓
          Array de Assentos em Memória
          (10 linhas × 6 colunas)
```

---

## 🛠️ Tecnologias & Stack

| Componente | Tech | Propósito |
|-----------|------|----------|
| Backend | C++17 | Servidor principal |
| Servidor | httplib.h | Tratamento HTTP |
| Dados | nlohmann/json | Parsing JSON |
| Frontend | HTML5/CSS3/JS | Interface |
| API | REST | Comunicação |

---

## 📁 Estrutura de Pastas

```
Aerofix-backend-project/
├── Air Travel Platform 2.0/        
│   ├── backend/
│   │   ├── main.cpp
│   │   ├── aerofix_api.exe
│   │   ├── httplib.h
│   │   ├── json.hpp
│   │   └── Dockerfile
│   └── frontend/
│       ├── index.html
│       ├── script.js
│       └── style.css
├── Air Travel Platform 1.1/        
├── Air Travel Platform 1.0/       
├── README.md                       (English)
├── README.pt-BR.md                 (Português)
└── License
```

---

## 🚀 Instalação

### Pré-requisitos
- **Compilador C++17** (GCC, Clang, MinGW)
- **Editor de Código** (VS Code recomendado)
- **Navegador** (Chrome, Firefox, Safari, Edge)

#### Windows (MinGW)
```bash
# Download: https://www.mingw-w64.org/
g++ --version
```

#### Linux
```bash
sudo apt install build-essential g++
g++ --version
```

#### macOS
```bash
xcode-select --install
```

---

## 🔨 Compilação & Execução

### Backend

```bash
cd "Air Travel Platform 2.0/backend"

# Windows
g++ -std=c++17 -O2 -o aerofix_api.exe main.cpp
./aerofix_api.exe

# Linux/macOS
g++ -std=c++17 -O2 -o aerofix_api main.cpp
./aerofix_api
```

**Saída:** `Iniciando servidor Aerofix Backend na porta 8080...`

### Frontend

```bash
cd "Air Travel Platform 2.0/frontend"

# VS Code Live Server (recomendado)
# Clique com botão direito em index.html → Open with Live Server

# Ou com Python
python -m http.server 8000

# Ou com Node.js
npx http-server
```

### Testar API

```bash
curl http://localhost:8080/assentos
```

---

## 📡 Endpoints da API REST

### GET /assentos

Obter status de todos os assentos

```bash
curl http://localhost:8080/assentos
```

Status: `"O"` = Disponível, `"X"` = Reservado

### POST /reservar/individual

Reservar assento individual

```bash
curl -X POST http://localhost:8080/reservar/individual \
  -H "Content-Type: application/json" \
  -d '{
    "classe": 1,
    "nome": "João Silva",
    "fileira": 3,
    "coluna": "B",
    "simular": false
  }'
```

**Ou com auto-recomendação:**
```json
{
  "classe": 2,
  "nome": "Maria Costa",
  "recomendacao": true,
  "pertoJanela": true,
  "simular": false
}
```

### POST /reservar/familia

Reservar para família (3-5 pessoas)

```bash
curl -X POST http://localhost:8080/reservar/familia \
  -H "Content-Type: application/json" \
  -d '{
    "classe": 1,
    "numPessoas": 4,
    "nomes": ["Ana", "Bruno", "Carlos", "Diana"],
    "simular": false
  }'
```

### POST /reservar/casal

Reservar para casal (2 pessoas)

```bash
curl -X POST http://localhost:8080/reservar/casal \
  -H "Content-Type: application/json" \
  -d '{
    "escolhaProximidade": 2,
    "nomes": ["Luis", "Ana"],
    "simular": false
  }'
```

**Opções de proximidade:**
- `1` = Assentos na janela (lados opostos)
- `2` = Assentos adjacentes

---

## ✨ Funcionalidades & Algoritmos

### Individual  ✈️
- Seleção manual ou automática
- Preferência de janela (Executiva)
- Validação em tempo real
- Modo simulação

### Família 👨‍👩‍👧‍👦
- Grupos de 3-5 pessoas
- Assentos adjacentes
- Distribuição inteligente
- Restrições de classe

### Casal 💑
- Separados (nas janelas)
- Adjacentes (mesma linha)

### Motor de Recomendação
- Busca inteligente
- Prioridade nas janelas
- Validação de classe
- Feedback instantâneo

---

## 🎫 Restrições de Classe

| Classe | A | B | C | D | E | F |
|--------|---|---|---|---|---|---|
| **Econômica** | ❌ | ✅ | ✅ | ✅ | ✅ | ❌ |
| **Executiva** | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

---

## 🛫 Fluxo de Reserva

```
Selecionar Tipo
    ↓
Escolher Classe
    ↓
Ver Assentos
    ↓
Selecionar Assentos
    ↓
Confirmar
    ↓
Sucesso
```

---

## 🤝 Como Contribuir

1. Faça um Fork do repositório
2. Crie uma branch: `git checkout -b feature/X`
3. Commit: `git commit -m 'Adicionar X'`
4. Push: `git push origin feature/X`
5. Abra um Pull Request

---

## 🗺️ Roadmap

- ✅ v2.0 - Interface web
- ⏳ v2.1 - Integração de pagamento
- ⏳ v3.0 - Múltiplos voos, banco de dados
- ⏳ v4.0 - App mobile, funcionalidades completas

---

## 👨‍💻 Autor

**Nicolas Harnisch** — [@NicolasHarnisch](https://github.com/NicolasHarnisch)

---

**⭐ Se foi útil, agradecemos uma estrela neste repositório!**