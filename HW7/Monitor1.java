/* Chris Fietkiewicz. Demonstrates ReentrantLock WITHOUT condition variables.
   Creates 2 threads for "add" function and prints global sum.
   Functionality is identical to monitor1.c.
*/

import java.util.concurrent.*;
import java.util.concurrent.locks.*;

class Monitor1 {
	private static Totaler totaler = new Totaler();

	public static void main(String[] args) throws InterruptedException {
		Thread add1 = new Thread(new Add(1));
		Thread add2 = new Thread(new Add(51));
		add1.start();
		add2.start();
		add1.join();
		add2.join();
		totaler.printSum();
	}

	private static class Add implements Runnable {
		private int start;
		
		public Add(int start) {
			this.start = start;
		}
		
		public void run() {
			for (int i = start; i <= start + 49; i++)
				totaler.addToSum(i);
		}
	}

	private static class Totaler {
		private int sum = 0;
		private static ReentrantLock mutex = new ReentrantLock();

		public void addToSum(int i) {
			mutex.lock();
			sum += i;
			mutex.unlock();
		}
		
		public void printSum() {
			System.out.println("sum = " + sum);
		}
	}
}