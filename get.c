#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_ZERO 48
#define ASCII_NINE 57
#define EQUAL 0
#define MAX_PRODUCTS 10
#define MAX_SALES 50
#define SIZE_OF_CPF 20
#define SIZE_OF_NAME 20
#define IDENTIFY_SALE 'S'
#define IDENTIFY_PRODUCT 'P'
#define AMOUNT_STEP 1
#define PRODUCT_NAME_STEP 2
#define TAX_FEE 0.15
#define OPERATIONAL_FEE 0.75

struct p
{
    char product_name[SIZE_OF_NAME];
    int amount;
    float unitary_value;
}typedef product;

struct s
{
    product cart[MAX_PRODUCTS];
    char client_name[SIZE_OF_NAME];
    char cpf[SIZE_OF_CPF];
    int number_of_valid_itens;
    float final_value;
} typedef sale;

int getAmountFromBuffer(char *buffer, int index_buffer);
float getValueFromBuffer(char *buffer, int index_buffer);
void printClientProperties(char *client_name, char *cpf);
void printItemOfCart(int amount, char *product_name, float unitary_value);

int get()
{
    //local variables
    char buffer[SIZE_OF_NAME];
    char file_name[] = "database.txt";
    FILE* file_pointer;
    int index_buffer = 0;
    int index_product = 0;
    int index_sale = 0;
    char next_ch;
    sale report[MAX_SALES];
    char state = IDENTIFY_SALE;
    int step = AMOUNT_STEP;
    char token[SIZE_OF_NAME];

    //handling file
    file_pointer = fopen(file_name, "r");
    if (file_pointer == NULL)
    {
        printf("impossivel abrir o arquivo %s\n", file_name);
        exit(1);
    }

    while ((next_ch = fgetc(file_pointer)) != EOF)
    {
        if ((next_ch >= ASCII_ZERO && next_ch <=ASCII_NINE) && state == IDENTIFY_PRODUCT)
        {
            //reading product
            do
            {
                if (next_ch == ';' && step == AMOUNT_STEP)
                {
                    //just make shure of \0
                    buffer[index_buffer] = '\0';

                    //get amount
                    report[index_sale].cart[index_product].amount = getAmountFromBuffer(buffer, index_buffer-1);
                    
                    //clear index_buffer
                    index_buffer = 0;

                    //to next step
                    step = PRODUCT_NAME_STEP;
                }
                else if (next_ch == ';' && step == PRODUCT_NAME_STEP) 
                {
                    //just make shure of \0
                    buffer[index_buffer] = '\0';

                    //get name product
                    strcpy(report[index_sale].cart[index_product].product_name, buffer);

                    //clear index_buffer
                    index_buffer = 0;

                    //reset step
                    step = AMOUNT_STEP;
                }
                else 
                {
                    //store in buffer
                    buffer[index_buffer] = next_ch;
                    index_buffer++;
                }
            } while ((next_ch = fgetc(file_pointer)) != '\n');

            //just make shure of \0
            buffer[index_buffer] = '\0';

            //Ready to get unitary value
            report[index_sale].cart[index_product].unitary_value = getValueFromBuffer(buffer, index_buffer-1);       

            //clear index_buffer
            index_buffer = 0;

            //keep getting products and dont change state
            index_product++;
        }
        else if (state == IDENTIFY_PRODUCT)
        {
            // it means that next_ch is a letter, so must close cart
            // must first get the number of valid itens in cart
            report[index_sale].number_of_valid_itens = index_product;

            // unget first letter of next sale
            ungetc(0,file_pointer);

            //change state, reset index_product and increase index_sale
            state = IDENTIFY_SALE;
            index_product = 0;
            index_sale++;
        }
        else
        {            
            while ((next_ch = fgetc(file_pointer)) != '\n')
            {
                if (next_ch == ';'){
                    //just make shure of \0
                    buffer[index_buffer] = '\0';

                    //client name ready to be stored
                    strcpy(report[index_sale].client_name, buffer);

                    //clear index_buffer
                    index_buffer = 0;
                }
                else
                {
                    //store in buffer
                    buffer[index_buffer] = next_ch;
                    index_buffer++;
                }
            }
            //just make shure of \0
            buffer[index_buffer] = '\0';

            //client cpf ready to be stored
            strcpy(report[index_sale].cpf, buffer);
            
            //clear index_buffer
            index_buffer = 0;

            //change state
            state = IDENTIFY_PRODUCT;
        }
    }
    // fot the last sale, it's needed to take last report as others
    // must first get the number of valid itens in cart
    report[index_sale].number_of_valid_itens = index_product;

    //change state, reset index_product and increase index_sale
    state = IDENTIFY_SALE;
    index_product = 0;
    index_sale++;

    //make report
    float invoicing = 0;
    float tax;
    float net_value;
    float operational_cost;
    float profit;
    for(int i = 0; i < index_sale; i++)
    {
        printClientProperties(report[i].client_name, report[i].cpf);
        float cart_value = 0;
        for(int j = 0; j < report[i].number_of_valid_itens; j++)
        {
            printItemOfCart(report[i].cart[j].amount, report[i].cart[j].product_name, report[i].cart[j].unitary_value);
            cart_value += report[i].cart[j].amount * report[i].cart[j].unitary_value;
        }
        invoicing += cart_value;
        printf("VALOR DA VENDA: %.2f\n", cart_value);
        printf("-----------------\n");
    }
    tax = invoicing*TAX_FEE;
    net_value = invoicing - tax;
    operational_cost = net_value*OPERATIONAL_FEE;
    profit = net_value - operational_cost;
    printf("FATURAMENTO: %.2f\n", invoicing);
    printf("IMPOSTO: %.2f\n", tax);
    printf("CUSTO OPERACIONAL: %.2f\n", operational_cost);
    printf("LUCRO: %.2f\n", profit);
    return 0;
}

int getAmountFromBuffer(char *buffer, int index_buffer)
{
    int amount = 0;
    int scale = 1;
    while (index_buffer > -1)
    {
        amount += (buffer[index_buffer] - ASCII_ZERO)*scale;
        scale *= 10;
        index_buffer--;
    }
    return amount;
    // O(n) 
}

float getValueFromBuffer(char *buffer, int index_buffer)
{
    float unitary_value = 0;
    float scale = 0.01;
    while (index_buffer > -1)
    {
        if (buffer[index_buffer] != '.')
        {
            unitary_value += (buffer[index_buffer] - ASCII_ZERO)*scale;
            scale *= 10;
        }
        index_buffer--;
    }
    return unitary_value;
}

void printClientProperties(char *client_name, char *cpf)
{
    printf("%s %s\n", client_name, cpf);
}
void printItemOfCart(int amount, char *product_name, float unitary_value)
{
    printf("%d - %s : %.2f => %.2f\n", amount, product_name, unitary_value, amount*unitary_value);
}