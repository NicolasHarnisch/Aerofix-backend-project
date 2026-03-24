let mapaAtual = []; 
let modoManualAtivo = false;
let cliquesRestantes = 0;
let nomesParaManual = []; // Guarda a fila de nomes que estão escolhendo

// URL da API corrigida. NUNCA coloque "/" no final.
const API_URL = "https://aerofix-backend-project.onrender.com";

async function carregarAssentos() {
    try {
        // CORREÇÃO: Usando o sinal de + para juntar a variável com o texto
        const resposta = await fetch(API_URL + '/assentos');
        if (!resposta.ok) throw new Error("Servidor não respondeu OK");
        const mapa = await resposta.json();
        mapaAtual = mapa; 
        desenharAviao(mapa);
    } catch (erro) {
        document.getElementById('aviao-grid').innerHTML = "<p style='color:red;'>Servidor offline. Verifique se o backend está rodando!</p>";
    }
}

function desenharAviao(mapaAssentos) {
    const grid = document.getElementById('aviao-grid');
    grid.innerHTML = ''; 
    mapaAssentos.forEach((fileira, index) => {
        const div = document.createElement('div');
        div.className = 'fileira';
        
        const numFileira = document.createElement('div');
        numFileira.className = 'num-fileira';
        numFileira.innerText = index + 1;
        div.appendChild(numFileira);
        
        fileira.forEach((poltrona, colIndex) => {
            const btn = document.createElement('button');
            btn.className = `poltrona ${poltrona.status === 'X' ? 'ocupado' : 'livre'}`;
            btn.innerText = poltrona.id;
            
            // SUPER UPGRADE: Ver o nome de quem reservou!
            if (poltrona.status === 'X') {
                btn.title = `Ocupado por: ${poltrona.ocupante}`;
            }
            
            btn.onclick = () => clicarPoltrona(index + 1, poltrona.id.charAt(0));
            div.appendChild(btn);
            
            if (colIndex === 2) {
                const corredor = document.createElement('div');
                corredor.className = 'corredor';
                div.appendChild(corredor);
            }
        });
        grid.appendChild(div);
    });
}

function mudarFormulario() {
    const plano = document.getElementById('tipo-plano').value;
    const classe = document.getElementById('classe-voo').value;
    const box = document.getElementById('opcoes-dinamicas');
    
    // NOME É OBRIGATÓRIO PARA TODOS
    let exNome = plano === 'individual' ? 'Ex: Nicolas' : plano === 'casal' ? 'Ex: Nicolas, Manu' : 'Ex: Pai, Mae, Filho';
    
    let htmlForm = `
        <label>Nome(s) (separados por vírgula):</label>
        <input type="text" id="nomes-reserva" placeholder="${exNome}" required>
    `;

    // Aviso da Família
    if (plano === 'familia') {
        htmlForm += `<p style="font-size: 0.85rem; color: #e74c3c; margin-top: 5px; font-weight: 500;">* Exclusivo para grupos de 3 a 5 pessoas.</p>`;
    }

    // AVISO DE PRIORIDADE DA EXECUTIVA (Aparece para TODOS os planos)
    if (classe === '2') {
        htmlForm += `<p style="font-size: 0.85rem; color: #2980b9; margin-top: 5px; font-weight: 600;">👑 Benefício Executiva: O sistema prioriza e garante assentos na Janela (A ou F).</p>`;
    }

    htmlForm += `
        <label style="margin-top: 15px; display: block;">Escolha o método:</label>
        <select id="metodo-reserva" onchange="atualizarOpcoesMetodo()">
            <option value="auto">Deixar o sistema escolher</option>
            <option value="manual">Escolher manualmente no mapa</option>
        </select>
        <div id="opcoes-metodo-auto" style="margin-top: 15px;">
    `;

    if (plano === 'individual') {
        if (classe === '2') { 
            htmlForm += `
                <label>Preferência (Executiva):</label>
                <select id="pref-janela">
                    <option value="sim">Perto da Janela</option>
                    <option value="nao">Corredor/Meio</option>
                </select>
            `;
        } else { 
            htmlForm += `<p style="font-size: 0.85rem; color: #555;">Na Econômica, poltronas são no centro.</p>`;
        }
    } 
    else if (plano === 'casal') {
        htmlForm += `<label>Preferência do Casal:</label><select id="pref-casal">`;
        if (classe === '2') { 
            htmlForm += `<option value="2">Próximos (Um na Janela)</option><option value="1">Separados (Ambos na Janela)</option><option value="3">Próximos (Longe da Janela)</option></select>`;
        } else { 
            htmlForm += `<option value="3">Próximos (Longe da Janela)</option></select><p style="font-size: 0.85rem; color: #555; margin-top:5px;">Econômica: casais sentam próximos no centro.</p>`;
        }
    }

    htmlForm += `</div>`; 
    box.innerHTML = htmlForm;

    document.getElementById('classe-voo').onchange = mudarFormulario;
    atualizarOpcoesMetodo();
}

function atualizarOpcoesMetodo() {
    const metodo = document.getElementById('metodo-reserva').value;
    const divAuto = document.getElementById('opcoes-metodo-auto');
    if (divAuto) divAuto.style.display = (metodo === 'auto') ? 'block' : 'none';
}

// CONGELA/DESCONGELA O PAINEL PARA O USUÁRIO NÃO FAZER BOBAGEM
function travarPainel(travar) {
    document.getElementById('tipo-plano').disabled = travar;
    document.getElementById('classe-voo').disabled = travar;
    document.getElementById('nomes-reserva').disabled = travar;
    document.getElementById('metodo-reserva').disabled = travar;
    
    // Transforma o botão Confirmar em Cancelar
    const btn = document.querySelector('.btn-reservar');
    if(travar) {
        btn.innerText = "Cancelar Seleção Manual";
        btn.style.backgroundColor = "#e74c3c";
        btn.onclick = cancelarModoManual;
    } else {
        btn.innerText = "Confirmar Reserva";
        btn.style.backgroundColor = "#1a5f7a";
        btn.onclick = enviarReserva;
    }
}

function cancelarModoManual() {
    modoManualAtivo = false;
    nomesParaManual = [];
    cliquesRestantes = 0;
    travarPainel(false);
    alert("Seleção manual cancelada.");
}

// CONTA SE TEM CADEIRAS LIVRES SUFICIENTES NAQUELA CLASSE! (Evita Overbooking)
function validarCapacidade(classe, qtdNecessaria) {
    let livres = 0;
    for (let f = 0; f < 10; f++) {
        for (let c = 0; c < 6; c++) {
            if (mapaAtual[f][c] && mapaAtual[f][c].status === 'O') {
                if (classe === 2) livres++; // Executiva tem todas as colunas
                else if (classe === 1 && c >= 1 && c <= 4) livres++; // Econômica só do meio
            }
        }
    }
    return livres >= qtdNecessaria;
}

async function enviarReserva() {
    const nomesRaw = document.getElementById('nomes-reserva').value;
    const nomes = nomesRaw.split(',').map(n => n.trim()).filter(n => n);
    
    if(nomes.length === 0) { alert("Por favor, digite o nome!"); return; }

    const plano = document.getElementById('tipo-plano').value;
    const classe = parseInt(document.getElementById('classe-voo').value);
    const metodo = document.getElementById('metodo-reserva').value;
    
    let url = '';
    let payload = { classe: classe, simular: true, nomes: nomes }; 
    let qtdAssentosNecessarios = nomes.length;

    // VALIDAÇÕES CRÍTICAS DE QUANTIDADE DE NOMES
    if (plano === 'individual' && qtdAssentosNecessarios !== 1) { alert("Plano Individual permite apenas 1 nome!"); return; }
    if (plano === 'casal' && qtdAssentosNecessarios !== 2) { alert("Plano Casal exige 2 nomes separados por vírgula!"); return; }
    if (plano === 'familia' && (qtdAssentosNecessarios < 3 || qtdAssentosNecessarios > 5)) { alert("Família exige de 3 a 5 nomes!"); return; }

    // VERIFICA SE O AVIÃO TEM LUGAR!
    if (!validarCapacidade(classe, qtdAssentosNecessarios)) {
        alert(`Não há ${qtdAssentosNecessarios} poltronas disponíveis nesta classe!`);
        return;
    }

    if (plano === 'individual') {
        if (metodo === 'manual') { iniciarSelecaoManual(nomes); return; }
        // CORREÇÃO: Usando o sinal de +
        url = API_URL + '/reservar/individual';
        payload.recomendacao = true;
        payload.nome = nomes[0]; // Rota individual espera "nome" no singular
        const selectJanela = document.getElementById('pref-janela');
        payload.pertoJanela = selectJanela ? (selectJanela.value === 'sim') : false;
    } 
    else if (plano === 'familia') {
        if (metodo === 'manual') { iniciarSelecaoManual(nomes); return; }
        // CORREÇÃO: Usando o sinal de +
        url = API_URL + '/reservar/familia';
        payload.numPessoas = qtdAssentosNecessarios;
    } 
    else if (plano === 'casal') {
        if (metodo === 'manual') { iniciarSelecaoManual(nomes); return; }
        // CORREÇÃO: Usando o sinal de +
        url = API_URL + '/reservar/casal';
        payload.escolhaProximidade = parseInt(document.getElementById('pref-casal').value);
    }

    try {
        const resposta = await fetch(url, { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify(payload) });
        const resultado = await resposta.json();

        if (resposta.ok) {
            const assentosSugeridos = resultado.assentos.join(", ");
            if (confirm(`O sistema sugere: ${assentosSugeridos}.\nConfirmar reserva para ${nomesRaw}?`)) {
                payload.simular = false;
                await fetch(url, { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify(payload) });
                alert("Reserva concluída com sucesso!");
                carregarAssentos();
            } else {
                iniciarSelecaoManual(nomes);
            }
        } else {
            alert(`O sistema não achou lugares juntos: ${resultado.erro}\nPor favor, escolha separadamente no mapa.`);
            iniciarSelecaoManual(nomes);
        }
    } catch (e) { alert("Servidor C++ offline ou erro de rede!"); }
}

function iniciarSelecaoManual(listaNomes) {
    modoManualAtivo = true;
    nomesParaManual = [...listaNomes];
    cliquesRestantes = nomesParaManual.length;
    travarPainel(true); // Bloqueia o formulário para o usuário não burlar!
    
    alert(`MÓDULO MANUAL ATIVADO!\n\nClique no mapa para escolher a poltrona do(a) passageiro(a): ${nomesParaManual[0]}`);
}

async function clicarPoltrona(fileira, coluna) {
    const fIdx = fileira-1;
    const cIdx = coluna.charCodeAt(0) - 65;
    
    if(!mapaAtual[fIdx] || !mapaAtual[fIdx][cIdx]) return;
    const poltronaAtual = mapaAtual[fIdx][cIdx];
    
    // IMPEDE CLIQUE PRECOCE! (Solução do seu bug)
    if (!modoManualAtivo) {
        if(poltronaAtual.status === 'X') return; // Clicou num vermelho atoa
        alert("⚠️ Selecione um plano à esquerda e clique em 'Confirmar Reserva' primeiro para iniciar a reserva.");
        return;
    }

    if(poltronaAtual.status === 'X') {
        alert("Poltrona já ocupada!"); return;
    }

    const classe = parseInt(document.getElementById('classe-voo').value);
    if (classe === 1 && (coluna === 'A' || coluna === 'F')) {
        alert("Atenção: A classe Econômica não permite assentos A e F (Janela)!"); return;
    }

    let nomePassageiro = nomesParaManual[0];
    if(!confirm(`Reservar a poltrona ${coluna}${fileira} para ${nomePassageiro}?`)) return;

    // CORREÇÃO: Usando o sinal de + para juntar a URL
    try {
        const resposta = await fetch(API_URL + '/reservar/individual', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ classe: classe, fileira: fileira, coluna: coluna, simular: false, recomendacao: false, nome: nomePassageiro })
        });

        if (resposta.ok) {
            carregarAssentos(); 
            nomesParaManual.shift(); // Remove o primeiro da fila
            cliquesRestantes--;
            
            if (cliquesRestantes <= 0) {
                modoManualAtivo = false;
                travarPainel(false); // Libera o sistema
                setTimeout(() => alert("Seleção manual finalizada com sucesso! Todas as poltronas foram reservadas."), 300);
            } else {
                setTimeout(() => alert(`Poltrona reservada!\nAgora clique no assento para o próximo passageiro(a): ${nomesParaManual[0]}`), 100);
            }
        } else {
            const res = await resposta.json();
            alert("Erro: " + res.erro);
        }
    } catch (e) {
        alert("Falha na comunicação ao clicar na poltrona.");
    }
}

// Configura o evento do botão de Confirmar
document.querySelector('.btn-reservar').onclick = enviarReserva;
window.onload = () => { mudarFormulario(); carregarAssentos(); };