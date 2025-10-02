package br.utfpr.rag.exeaulas.threads;

public class Principal {

	public static void main(String args[]) {
		
		// Declarando o que será compartilhado.		
		Compartilhado var = new Compartilhado();
		
		// Instancia os dois amigos.		
		Thread t0 = new Thread(new ThreadX(var,"T1", "T0"));
		Thread t1 = new Thread(new ThreadX(var, "T0", "T1"));

		// Batiza eles.
		t0.setName("T0");
		t1.setName("T1");
		
		// Inicia as threads.
		t0.start();
		t1.start();
		try {
			Thread.currentThread().sleep(5000);
		} catch (InterruptedException e) {
		}

		var.dizerPara("Principal", "Terminou");
		try {
			Thread.currentThread().sleep(100);
		} catch (InterruptedException e) {
		}
	}
}
