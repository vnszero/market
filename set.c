#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fileHandler.h"

int set() {
	clear("database.txt");	
	char cpfs[50][14];
	char reportFile[500];
	char auxBuffer[500];
	int qtdVendas = 0;
	float faturamento = 0;
	float imposto = 0;
	float lucro = 0;
	printf("Quantas vendas foram efetuadas? ");
	scanf("%d", &qtdVendas);
	for (int i = 0; i < qtdVendas; i++) {
		printf("Digite o cpf da compra: ");
		scanf(" %14[^\n]", cpfs[i]);
		sprintf(reportFile, "#Cliente%d;%s\n",i+1,cpfs[i]);
		save("database.txt", reportFile);
		int qtdItens = 0;
		printf("Quantos itens dessa venda foram comprados? ");
		scanf("%d",&qtdItens);
		float vendas[20][3];
		char nomesProdutos[20][50];
		float totalVenda = 0;
		for (int j = 0; j < qtdItens; j++) {
			printf("Digite o nome do produto: ");
			scanf(" %20[^\n]", nomesProdutos[j]);
			printf("Digite a quantidade comprada: ");
			scanf("%f",&vendas[j][0]);
			printf("Digite o valor unitario: ");
			scanf("%f", &vendas[j][1]);
			vendas[j][2] = vendas[j][0] * vendas[j][1];
			totalVenda += vendas[j][2];
			sprintf(reportFile, "%.1f;", vendas[j][0]);
			save("database.txt", reportFile);
			for (int k=0; nomesProdutos[j][k] != '\0'; k++){ 
				if (nomesProdutos[j][k] >= 'a' && nomesProdutos[j][k] <= 'z' || nomesProdutos[j][k] >= 'A' && nomesProdutos[j][k] <= 'Z' || nomesProdutos[j][k] == ' ') {
					auxBuffer[k] = nomesProdutos[j][k];
					sprintf(reportFile, "%c", nomesProdutos[j][k]);
					save("database.txt", reportFile);
				}
			}
			sprintf(reportFile, ";%.1f\n", vendas[j][1]);
			save("database.txt", reportFile);
		}
		// sprintf(reportFile, "Total da compra: %.2f\n", totalVenda);
		// save("database.txt", reportFile);
		faturamento += totalVenda;
	}
	imposto = faturamento * 0.15;
	float liquido = faturamento - imposto;
	float lucroFinal = liquido * 0.25;
	// sprintf(reportFile, "FATURAMENTO: %.2f\n", faturamento);
	// save("database.txt", reportFile);
	// sprintf(reportFile, "IMPOSTO: %.2f\n", imposto);
	// save("database.txt", reportFile);
	// sprintf(reportFile, "LUCRO: %.2f\n", lucroFinal);
	// save("database.txt", reportFile);
	return 0;
}