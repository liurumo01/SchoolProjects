package space.snowwolf.pi.data;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class HttperfOutputHandler {

	public static void main(String[] args) throws FileNotFoundException {

		Scanner sc = new Scanner(new File("a.txt"));
		StringBuilder b = new StringBuilder();
		List<String> list = new ArrayList<>();

		//第一行数据有问题，首字母不是'['？
//		sc.nextLine();
//		sc.nextLine();

		//去除无意义内容
		filter : while (sc.hasNextLine()) {
			String line = sc.nextLine();
//			if (line.startsWith("[")) {
//				sc.nextLine();
//				line = sc.nextLine();
//			}
			while(line.length() > 0 && Character.isDigit(line.charAt(0))) {
				String[] split = line.split(" ");
				list.add(split[4]);
				if(sc.hasNextLine()) {
					line = sc.nextLine();					
				} else {
					break filter;
				}
			}
			if(line.startsWith("httperf")) {
				line = sc.nextLine();
			}
			if (!line.equals("") && !line.contains("parse_status_line") && !line.contains("get_line")
					&& !line.contains("warning")) {
				b.append(line).append("\n");
			}

		}
		sc.close();

		//将所有非数字字符替换成空格
		String s1 = "abcdefghijklmnopqrstuvwxyz";
		String s2 = s1.toUpperCase();
		String s3 = "[]:/-=(),%<>\n*^";
		String s = s1 + s2 + s3;

		String str = b.toString();
		for (int i = 0; i < s.length(); i++) {
			str = str.replace(s.charAt(i), ' ');
		}

		//连续的多个空格只留下一个，行首空格删除
		b = new StringBuilder(str);
		for (int i = 0; i < b.length(); i++) {
			while (b.charAt(i) != ' ') {
				i++;
			}
			int j = i + 1;
			while (j < b.length()) {
				if (b.charAt(j) != ' ') {
					break;
				}
				j++;
			}
			b.delete(i + 1, j);
			i++;
		}
		while (b.charAt(0) == ' ') {
			b.deleteCharAt(0);
		}

		//将余下的字符串按照空格分割，得到包含数字的字符串数组，再解析成 double 数组
		str = b.toString();
		String[] split = str.split(" ");
		double[][] arr = new double[20][57];
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 57; j++) {
				arr[i][j] = Double.parseDouble(split[i * 57 + j]);
			}
		}
	
		//按照表格格式打印
		String[] title = {
				"maximnu connext burst length",
				"total connections",
				"total requests",
				"total replies",
				"total test-duration (s)",
				"connection rate ? conn/s",
				"connection rate ? ms/conn",
				"connection rate <= ? concurrent connections",
				"connection time min (ms)",
				"connection time avg (ms)",
				"connection time max (ms)",
				"connection time median (ms)",
				"connection time stddev (ms)",
				"connection time connect (ms)",
				"connection length (replies/conn)",
				"request rate (req/s)",
				"request rate (ms/req)",
				"request size (B)",
				"reply rate min (replies/s)",
				"reply rate avg (replies/s)",
				"reply rate max (replies/s)",
				"reply rate stddev (replies/s)",
				"reply rate samples (replies/s)",
				"reply time response (ms)",
				"reply time transfer (ms)",
				"reply size header (B)",
				"reply size content (B)",
				"reply size footer (B)",
				"reply size total (B)",
				"reply status 1xx",
				"reply status 1xx",
				"reply status 2xx",
				"reply status 2xx",
				"reply status 3xx",
				"reply status 3xx",
				"reply status 4xx",
				"reply status 4xx",
				"reply status 5xx",
				"reply status 5xx",
				"cpu time user (s)",
				"cpu time system (s)",
				"cpu time user (%)",
				"cpu time system (%)",
				"cpu time total (%)",
				"net I/O (KB/s)",
				"net I/O (?*?^?)",
				"net I/O (?*?^?)",
				"net I/O (?*?^?)",
				"errors total",
				"errors client-timo",
				"errors socket-timo",
				"errors connrefused",
				"errors connreset",
				"errors fd-unavail",
				"errors addrunavail",
				"errors ftab-full",
				"errors other"
		};
		for (int i = 0; i < title.length; i++) {
			System.out.printf("%s\t", title[i]);
		}
		System.out.println();
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 57; j++) {
				System.out.printf("%-36.4f\t", arr[i][j]);
			}
			System.out.println();
		}
		
		for(int i = 0; i < list.size(); i+=2) {
			System.out.println(list.get(i) + "\t" + list.get(i + 1));
		}
		
	}

}
