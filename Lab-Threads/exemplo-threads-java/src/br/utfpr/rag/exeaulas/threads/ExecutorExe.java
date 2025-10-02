package br.utfpr.rag.exeaulas.threads;

import java.util.concurrent.Executor;

public class ExecutorExe implements Executor {
    
	public void execute(Runnable r) {
        new Thread(r).start();
    }
}
