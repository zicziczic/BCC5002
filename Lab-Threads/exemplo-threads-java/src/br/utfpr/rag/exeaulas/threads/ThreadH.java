package br.utfpr.rag.exeaulas.threads;

public class ThreadH extends Thread {

	private int delay;

	public ThreadH(String identificacao, int delay) {
		super(identificacao);
		this.delay = delay;
	}

	public void run() {
		String identificacao = this.getName();
		try {
			sleep(delay);
		} catch (InterruptedException e) {
			System.out.println("Thread: " + identificacao + " foi interrompida");
		}
		System.out.println(">>" + identificacao + " " + delay);
	}
}
