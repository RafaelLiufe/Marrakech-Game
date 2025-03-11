<p align="center"><a href="https://laravel.com" target="_blank"><img src="https://b1803394.smushcdn.com/1803394/wp-content/uploads/2022/06/marrakech-review-header-990x557.jpg?lossy=1&strip=1&webp=1" width="400" alt="Marrakech Logo"></a></p>

## Instruções para inicializar reposotório git:

### Clonar repositório com todas as brach:
```sh
git clone https://github.com/Otavio-Ferreira/Marrakech-Game
```

### Entrar no Diretório do Projeto:
```sh
git cd Marrakech-Game
```

### Verificar as Branches Remotas:
```sh
git branch -r
```
###  Configurar Git Flow no Projeto:
```sh
git flow init
```
### Acessar e Criar as Branches Localmente:
```sh
git checkout -b feature/otavio origin/feature/otavio
git checkout -b feature/kayky origin/feature/kayky
git checkout -b feature/rafael origin/feature/rafael
```

## Instruções git:

### Atualizar repositório local e remoto (Fazer ao parar de codar). Essa instrução também é conhecida como "Fazer o commit":
```sh
git add .
git commit -m "Descricao do que foi feito"
git push
```

###  Mudar de branch:
```sh
git checkout nome_da_branch
```

###  Atualizar seu repositório local na branch em que você está:
```sh
git pull
```