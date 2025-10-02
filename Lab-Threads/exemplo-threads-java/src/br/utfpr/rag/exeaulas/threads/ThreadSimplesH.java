package br.utfpr.rag.exeaulas.threads;
public class ThreadSimplesH extends Thread {

	public ThreadSimplesH(String str) {
		super(str);
	}

	public void run() {
		for (int i = 0; i < 10; i++) {
			System.out.println(i + " " + getName());
			try {
				sleep((long) (Math.random() * 1000));
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		System.out.println("[ThreadSimplesH]: Feito: " + getName());
	}
}