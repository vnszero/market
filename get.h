#ifndef GET_H_

int getAmountFromBuffer(char *buffer, int index_buffer);
float getValueFromBuffer(char *buffer, int index_buffer);
void printClientProperties(char *client_name, char *cpf);
void printItemOfCart(int amount, char *product_name, float unitary_value);
int get();

#endif