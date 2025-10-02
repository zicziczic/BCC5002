package br.utfpr.rag.exeaulas.threads;

import java.util.concurrent.ExecutorService;


import java.util.concurrent.Executors;

public class AlunosThreadsDemo {
	public static void main(String[] args) {
	
		ThreadSimplesH ts1 = new ThreadSimplesH("Huguinho");
		ts1.setPriority(Thread.MIN_PRIORITY);
		// ts1.start();
		
		ThreadSimplesI ts2 = new ThreadSimplesI();
		//ts2.run();
				
		/*System.out.println("Minima: " + Thread.MIN_PRIORITY);
		System.out.println("Normal: " + Thread.NORM_PRIORITY);
		System.out.println("Maxima: " + Thread.MAX_PRIORITY);
						
		
		ThreadSimplesH ts3 = new ThreadSimplesH("Luizinho");
		ts3.start();
		
		System.out.println("Prioridade do Luizinho: " + ts3.getPriority());
		
		// Criando as threads e disparando
		
		new ThreadSimplesH("Buba").start();
		new ThreadSimplesH("Zezinho").start();
		new ThreadSimplesH("Tio Patinhas").start();
		new ThreadSimplesH("Capitão Boing").start();*/
		
		// Usando o executor criado.
		ExecutorExe executor = new ExecutorExe();
		// executor.execute(ts1);
		
		// Usando os executores.
		ExecutorService pool = Executors.newCachedThreadPool();
		pool.execute(ts1);
		
		// new ThreadSimplesI().run();
		
		pool.execute(new ThreadSimplesI());
		
		pool.execute(new ThreadSimplesI());
		
		pool.execute(new ThreadSimplesI());
		
		pool.execute(new ThreadSimplesI());
		
		
		
		pool.shutdown();
		
	}
}