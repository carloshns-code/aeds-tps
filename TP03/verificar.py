# Ferramenta OPCIONAL de auditoria; o programa principal e inteiramente em C.
from pathlib import Path
from collections import Counter
import sys

def ler(caminho):
    linhas = Path(caminho).read_text().splitlines()
    n = int(linhas[0])
    registros = [tuple(linha.split()) for linha in linhas[1:] if linha.strip()]
    if len(registros) != n or any(len(r) != 4 for r in registros):
        raise ValueError(f'Formato ou quantidade incorreta: {caminho}')
    return registros

def chave(r):
    return (int(r[3]), int(r[0]))

if len(sys.argv) != 4:
    sys.exit('Uso: python verificar.py entrada.txt selection.txt quick.txt')
origem = ler(sys.argv[1])
for caminho in sys.argv[2:]:
    resultado = ler(caminho)
    if Counter(origem) != Counter(resultado):
        sys.exit(f'ERRO: registros perdidos, duplicados ou alterados em {caminho}')
    if list(map(chave, resultado)) != sorted(map(chave, origem)):
        sys.exit(f'ERRO: ordenacao incorreta em {caminho}')
    print(f'OK: {caminho} - {len(resultado)} registros preservados e ordenados')
