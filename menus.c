
char menu(void) {
	char opcao;
	printf("Menu: ");
	scanf(" %c", &opcao);
	limpaBufferStdin();
	return toupper(opcao);

}
