package space.snowwolf.pi.data;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.LinkedList;
import java.util.ListIterator;

public class PowerDataHandler {

	public static void main(String[] args) throws IOException {
		LinkedList<PowerNode> PowerNodes = read();
		checkDuplicated(PowerNodes);
		checkMissing(PowerNodes);
		save(PowerNodes);
	}

	private static final String in = "power3.txt";
	 private static final String out = "power4.txt";

	private static void save(LinkedList<PowerNode> items) throws IOException {
		double max, min;
		PowerNode t = items.getFirst();
		min = max = t.power;
		BufferedWriter outWriter = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(out)));
		ListIterator<PowerNode> it = items.listIterator();
		while (it.hasNext()) {
			t = it.next();
			if (t.power > max) {
				max = t.power;
			}
			if (t.power < min) {
				min = t.power;
			}
			outWriter.write(t.toString());
			outWriter.newLine();
		}
		System.out.println("save : done!");
		System.out.println(new Date());
		outWriter.close();
	}

	private static void checkMissing(LinkedList<PowerNode> items) {
		Date d = new Date(items.getFirst().time.getTime());
		d = nextSecond(d);
		ListIterator<PowerNode> it = items.listIterator();
		it.next();
		Date startMiss = new Date();
		while (it.hasNext()) {
			if (!it.next().time.equals(d)) {
				startMiss.setTime(d.getTime());
				double p = 0;
				it.previous();
				for (int i = 0; i < 3; ++i) {
					p += it.previous().power;
				}
				for (int i = 0; i < 3; ++i) {
					it.next();
				}
				it.add(new PowerNode(d, p / 3.0));
			}
			d = nextSecond(d);
		}
		System.out.println("check miss : done!");
	}

	private static void checkDuplicated(LinkedList<PowerNode> items) {
		ListIterator<PowerNode> it = items.listIterator();
		PowerNode x = it.next();
		while (it.hasNext()) {
			PowerNode y = it.next();
			if (x.time.equals(y.time)) {
				it.remove();
			}
			x = y;
		}
		System.out.println("check dup : done!");
	}

	private static LinkedList<PowerNode> read() throws IOException {
		BufferedReader inReader = new BufferedReader(new FileReader(in));
		LinkedList<PowerNode> items = new LinkedList<PowerNode>();
		String record;
		while ((record = inReader.readLine()) != null) {
			items.add(new PowerNode(record));
		}
		System.out.println(items.size());
		inReader.close();
		return items;
	}

	private static final long oneDay = 24 * 3600 * 1000;

	private static Date nextSecond(Date t) {
		t.setTime(t.getTime() + 1000);
		if (t.getTime() % oneDay == oneDay / 24 * 16) {
			if (t.getTime() < 365 * oneDay) {
				t.setTime(t.getTime() - oneDay);
			}
		}
		return t;
	}

}

class PowerNode {

	Date time;
	double power;
	
	static DateFormat df = new SimpleDateFormat("HH:mm:ss");
	static NumberFormat pf = new DecimalFormat(".0");
	
	public PowerNode(Date time, double power) {
		this.time = new Date(time.getTime());
		this.power = power;
	}

	public PowerNode(String record) {
		String[] split = record.split("\t");
		try {
			time = df.parse(split[1]);
		} catch (ParseException e) {
			System.out.println("unrecognized!");
			e.printStackTrace();
		}
		power = Double.parseDouble(split[3]);
	}
	
	@Override
	public String toString() {
		NumberFormat pf = new DecimalFormat(".0");
		String p = pf.format(power);
		return df.format(time) + "\t" + p;
	}

}
