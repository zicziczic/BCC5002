package br.utfpr.rag.exeaulas.threads;

public class MultiThread {
	public static void main(String[] args) {
		ThreadH t1, t2, t3;
		t1 = new ThreadH("Primeira", (int) (Math.random() * 8000));
		t2 = new ThreadH("Segunda", (int) (Math.random() * 8000));
		t3 = new ThreadH("Terceira", (int) (Math.random() * 8000));
		
		t1.start();
		t2.start();
		t3.start();
	}
}