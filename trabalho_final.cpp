#include <windows.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <conio.h>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int main()
{
	//setlocale(LC_ALL, "Portuguese");
	vector<string> coordenadas;
	vector<string>::iterator ponteiro;
	vector<double> latitude;
	vector<double>::iterator ponteiro_latitude;
	vector<double> longitude;
	vector<double>::iterator ponteiro_longitude;
	
	//Solicitar ao usuário nome do arquivo .csv
	string arquivo;
	cout << "Digite o nome do arquivo " << endl;
	cin >> arquivo;
	arquivo = arquivo + ".csv";
	
	//Ler arquivo .csv
	cout << "Lendo o arquivo..." << endl << endl;
	string linha;

	ifstream meuarquivo(arquivo.c_str(), ifstream::in);
	if(meuarquivo.is_open())
	{
		coordenadas.clear();
		while (! meuarquivo.eof())
		{
			getline (meuarquivo, linha);
			//Transferir dados do arquivo para uma struct
			coordenadas.push_back(linha);
		}
		meuarquivo.close();
		cout << "Arquivo lido com sucesso!" << endl << endl;
	}
	else
		cout << "Não foi possível abrir o arquivo " << endl;
	
	coordenadas.erase(coordenadas.begin());
	
	/*cout << endl << "Vetor coordenadas: " << endl;
	for(ponteiro = coordenadas.begin(); ponteiro != coordenadas.end(); ponteiro++)
		cout << *ponteiro << endl;*/
	
	// Vector of string to save tokens
	vector<string> tokens;
	vector<string>::iterator ponteiro_t;
	for(ponteiro = coordenadas.begin(); ponteiro != coordenadas.end(); ponteiro++)
	{
	    // stringstream class check1 
	    stringstream check1(*ponteiro);
	    
	    string intermediate; 
	    
	    // Tokenizing w.r.t. space ',' 
	    while(getline(check1, intermediate, ',')) 
	    { 
			tokens.push_back(intermediate); 	
	   }
	}
	
	/*cout << endl << "Vetor tokens: " << endl;
	for(ponteiro_t = tokens.begin(); ponteiro_t != tokens.end(); ponteiro_t++)
		cout << *ponteiro_t << endl;*/
	
	
	for(ponteiro_t = tokens.begin(); ponteiro_t != tokens.end(); ponteiro_t = ponteiro_t + 3)
	{
		double numero = 0;
		stringstream conversao;
		conversao.str(*ponteiro_t);
		conversao >> numero;
		//cout << "numero lat convertido: " << numero << endl;
		latitude.push_back(numero);
	}
	
	/*cout << endl << "Vetor latitude: " << endl;
	for(ponteiro_latitude = latitude.begin(); ponteiro_latitude != latitude.end(); ponteiro_latitude++)
		cout << setprecision(9) << *ponteiro_latitude << endl;*/
	
	for(ponteiro_t = tokens.begin() + 1; ponteiro_t <= tokens.end(); ponteiro_t = ponteiro_t + 3)
	{		
		double numero = 0;
		stringstream conversao;
		conversao.str(*ponteiro_t);
		conversao >> numero;
		//cout << "numero long convertido: " << numero << endl;
		longitude.push_back(numero);
	}
	
	/*cout << endl << "Vetor longitude: " << endl;
	for(ponteiro_longitude = longitude.begin(); ponteiro_longitude != longitude.end(); ponteiro_longitude++)
		cout << setprecision(9) << *ponteiro_longitude << endl;*/
	
	//Solicitar volume de transporte ao usuário
	float volume_i;
	vector<float> volume;
	vector<float>::iterator ponteiro_volume;
	
	for(ponteiro_t = tokens.begin() + 2; ponteiro_t <= tokens.end(); ponteiro_t = ponteiro_t + 3)
	{
		cout << "Digite o volume de transporte desejado para: " << *ponteiro_t << endl;
		cin >> volume_i;
		volume.push_back(volume_i);
	}
	
	//Tarifa de transporte
	float tarifa;
	cout << "Digite a tarifa de transporte: " << endl;
	cin >> tarifa;
	
	//Aplicação da fórmula
	float somatorio_latitude = 0;
	float somatorio_longitude = 0;
	float divisor = 0;
	
	for(int i = 0 ; i < latitude.size(); i++)
	{
		somatorio_latitude = somatorio_latitude + (latitude[i] * volume[i]);
	}
	
	somatorio_latitude = somatorio_latitude*tarifa;
	
	for(int i = 0 ; i < longitude.size(); i++)
	{
		somatorio_longitude = somatorio_longitude + (longitude[i] * volume[i]);
	}
	
	somatorio_longitude = somatorio_longitude*tarifa;
	
	for(int i = 0 ; i < volume.size(); i++)
	{
		divisor = divisor + (volume[i] * tarifa);
	}
	
	float resultado_latitude = 0;
	float resultado_longitude = 0;
	
	resultado_latitude = somatorio_latitude/divisor;
	resultado_longitude = somatorio_longitude/divisor;
	
	cout << endl << "Coordenada final latitude longitude: " << endl << endl << "Latitude: " << resultado_latitude << " e " << "Longitude: " << resultado_longitude << endl << endl;
	
	int comando = 0;
	cout << "<1> Abrir localizacao no Google Maps" << endl; 
	cout << "<2> Finalizar analise" << endl; 
	cin >> comando;
	
	if(comando == 1)
	{
		char pesquisa[250];
		cout << "Enviando coordenadas ao Google Maps... " << endl;
		sprintf (pesquisa,"%s%f%s%f","C:\\\"Program Files (x86)\"\\Google\\Chrome\\Application\\chrome http://maps.google.com/?q=", resultado_longitude, "," , resultado_latitude);
		//cout << pesquisa << endl;
		system(pesquisa);
	}
	
	return 0;
}
