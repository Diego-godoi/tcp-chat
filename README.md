# 💬 TCP Chat P2P

Um chat **peer-to-peer** via TCP escrito em C, onde dois usuários se conectam diretamente — sem servidor central. As mensagens são salvas localmente em banco de dados SQLite, e o histórico de conversas é exibido automaticamente ao reconectar com um IP já conhecido.

---

## ✨ Funcionalidades

- Hospedar uma sala e aguardar alguém conectar
- Conectar diretamente ao IP de um amigo
- Histórico de mensagens salvo por IP (SQLite)
- Histórico exibido automaticamente ao reconectar com o mesmo IP
- Envio e recebimento simultâneo (threads)
- Comando `/sair` para encerrar o chat

---

## 🏗️ Arquitetura em Camadas

O projeto segue uma arquitetura em camadas, onde cada pasta tem uma responsabilidade bem definida:

```
tcp-chat/
├── main.c          → Entry point: menu e fluxo principal
├── net/            → Camada de Rede (sockets TCP)
│   ├── net.h
│   └── net.c
├── chat/           → Camada de Serviço (lógica do chat, threads)
│   ├── chat.h
│   └── chat.c
├── db/             → Camada de Dados (SQLite)
│   ├── db.h
│   └── db.c
├── ui/             → Camada de Apresentação (terminal)
│   ├── ui.h
│   └── ui.c
└── makefile
```

| Camada  | Responsabilidade                                  |
| ------- | ------------------------------------------------- |
| `net/`  | Criar sockets, conectar, aceitar, enviar, receber |
| `chat/` | Loop do chat, threads de envio e recebimento      |
| `db/`   | Salvar e buscar mensagens no SQLite por IP        |
| `ui/`   | Menu, inputs do usuário, exibição de mensagens    |

---

## 🔄 Como funciona o P2P

```
Pessoa A (host)             Pessoa B (guest)
       │                          │
  Abre uma porta                  │
  Aguarda conexão                 │
       │◄─────────────────────────┤
       │     B conecta ao IP:porta de A
       │                          │
       │◄────── mensagem ─────────│
       │─────── mensagem ─────────►│
       │                          │
  Ambos salvam no banco local (chat.db)
```

Cada pessoa roda o **mesmo programa** e escolhe o papel (hospedar ou conectar) no menu.

---

## 🛠️ Dependências

- GCC
- pthread (já incluso no Linux)
- SQLite3

Instale o SQLite no Arch Linux:

```bash
sudo pacman -S sqlite
```

Ou no Ubuntu/Debian:

```bash
sudo apt install libsqlite3-dev
```

---

## 🚀 Como compilar e rodar

```bash
# Compilar
make

# Rodar
./tcpchat
```

---

## 🧪 Testando na mesma máquina

Abra dois terminais:

**Terminal 1 — hospedar:**

```bash
./tcpchat
# Escolha: 1 (Hospedar)
# Porta: 8080
```

**Terminal 2 — conectar:**

```bash
./tcpchat
# Escolha: 2 (Conectar)
# IP: 127.0.0.1
# Porta: 8080
```

---

## 📖 Histórico de conversas

As mensagens são salvas no arquivo `chat.db` (SQLite), associadas ao IP do peer.

Na próxima vez que você se conectar ao mesmo IP, o histórico aparece automaticamente antes do chat iniciar:

```
── Histórico com 192.168.1.10 ──
  [2024-01-15 10:32:11] Diego: oi
  [2024-01-15 10:32:15] João: olá!
────────────────────────────────
```

---

## 💡 Comandos disponíveis no chat

| Comando | Ação                              |
| ------- | --------------------------------- |
| `/sair` | Encerra a conexão e volta ao menu |

---
