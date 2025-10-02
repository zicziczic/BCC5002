package br.utfpr.rag.exeaulas.threads;

public class ThreadX implements Runnable {
	
	Compartilhado minhaVariavel;
	String meuParceiro;
	String eu;
	
	public ThreadX(Compartilhado var, String parceiro, String peu) {
		minhaVariavel = var;
		meuParceiro = parceiro;
		eu = peu;
	}

	public void run() {
		// while (minhaVariavel.dizerPara((Math.floor(Math.random() + 0.25) == 0)? meuParceiro : eu , "Olá meu Parceiro."));
		while (minhaVariavel.dizerPara(meuParceiro , "Olá meu Parceiro."));
	}
}
