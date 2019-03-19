/* Chris Fietkiewicz. Demonstrates monitor rules with condition variables.
   Functionality is identical to monitor2.c.
Does the following steps:
1. Creates 2 threads for "add" function.
   Each thread computes a sum (1-50 or 51-100) and signals a cond. var.
2. Creates 3rd thread for "total" function which waits on "add" threads.
*/

import java.util.concurrent.*;
import java.util.concurrent.locks.*;

class Monitor2 {
	private static Monitor monitor = new Monitor();

	public static void main(String[] args) throws InterruptedException {
		Thread add1 = new Thread(new Add(1));
		Thread add2 = new Thread(new Add(51));
		Thread total = new Thread(new Total());
		add1.start();
		add2.start();
		total.start();
	}

	private static class Add implements Runnable {
		private int start;
		
		public Add(int start) {
			this.start = start;
		}
		
		public void run() {
			for (int i = start; i <= start + 49; i++)
				monitor.addToSum(i);
			monitor.addDone();
		}
	}

	private static class Total implements Runnable {
		public void run() {
			monitor.printSum();
		}
	}

	private static class Monitor {
		private int sum = 0;
		private int doneCount = 0;
		private static ReentrantLock mutex = new ReentrantLock();
		private static Condition addDone = mutex.newCondition();

		public void addToSum(int i) {
			mutex.lock();
			sum += i;
			mutex.unlock();
		}
		
		public void printSum() {
			mutex.lock();
			try {
				if (doneCount < 1)
					addDone.await();
				if (doneCount < 2)
					addDone.await();
			}
			catch (InterruptedException e) {}
			finally {
				System.out.println("sum = " + sum);
				mutex.unlock();
			}
		}
		
		public void addDone() {
			mutex.lock();
			doneCount++;
			addDone.signal();
			mutex.unlock();
		}
	}
}