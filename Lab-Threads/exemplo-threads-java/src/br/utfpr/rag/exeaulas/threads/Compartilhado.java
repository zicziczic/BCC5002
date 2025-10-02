package br.utfpr.rag.exeaulas.threads;

public class Compartilhado {
	
	String ultimoQueDisse = "T0";
	
	public synchronized boolean dizerPara(String pthread, String msg) {

		String euCorrente = Thread.currentThread().getName();
		
		// System.out.println("euCorrente: " + euCorrente);
		// System.out.println("pthread: " + pthread);
		// System.out.println("Random: " + Math.floor(Math.random() + 0.25));
		
		if (euCorrente.compareTo(pthread) != 0) {
			System.out.println( euCorrente + " dizendo para " + pthread + ": " + msg  );
			ultimoQueDisse = euCorrente;
			notifyAll();
			try {
				wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		} else {
			System.out.println(euCorrente + " está falando com ele mesmo: (" + euCorrente + "," + pthread + ")");
			return false;
		}
		return true;
	}
}
