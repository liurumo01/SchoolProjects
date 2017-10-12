package space.snowwolf.video.servlet;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;

public class VideoController extends HttpServlet {

	private static final long serialVersionUID = 4037333754626458111L;

	private ServerSocket server;
	private DateFormat format;
	
	@Override
	public void init(ServletConfig config) throws ServletException {
		
		super.init(config);
		format = new SimpleDateFormat("yyyyMMDDHHmmssSSS");
		
		String videoPath = config.getInitParameter("video-path");
		getServletContext().setAttribute("video-path", videoPath);
		
		File dir = new File(videoPath);
		if(!dir.exists()) {
			dir.mkdirs();
		}
		
		int uploadPort = Integer.parseInt(config.getInitParameter("upload-port"));
		try {
			server = new ServerSocket(uploadPort);
			System.out.println("File upload ServerSocket start at port " + uploadPort);
		} catch (IOException e) {
			e.printStackTrace();
			return;
		}
		
		new Thread(() -> {
			
			Socket client = null;
			try {
				while((client = server.accept()) != null) {
					System.out.println("Client connected : " + client);
					
					InputStream in = client.getInputStream();
					OutputStream out = client.getOutputStream();
					BufferedReader reader = new BufferedReader(new InputStreamReader(in));
					BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(out));
					
					String fileName = reader.readLine();
					fileName = fileName.substring(0, fileName.lastIndexOf(".")) + "-" + format.format(new Date()) + ".mp4";
					FileOutputStream fout = new FileOutputStream(videoPath + "/" + fileName);
					System.out.println("Start to upload file : " + fileName);
					
					long size = Long.parseLong(reader.readLine());
					int bufSize = 1048576;
					
					byte[] buf = new byte[bufSize];
					while(size > 0) {
						int len = in.read(buf, 0, size > bufSize ? bufSize : (int)size);
						fout.write(buf, 0, len);
						size -= len;
					}
					fout.flush();
					System.out.println("File upload finished : " + fileName + ", size = " + size);
					
					writer.write("Done.");
					writer.newLine();
					writer.flush();
					System.out.println("File upload status write back : " + client);
					
					fout.close();
					client.close();
					System.out.println("Close connection : " + client);
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
			
		}).start();
		
	}
	
	public boolean upload(File file, String ip, int port) {
		Socket socket = null;
		FileInputStream fin = null;
		
		try {
			socket = new Socket(ip, port);
			InputStream in = socket.getInputStream();
			OutputStream out = socket.getOutputStream();
			BufferedReader reader = new BufferedReader(new InputStreamReader(in));
			BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(out));
			
			long size = file.length();
			writer.write(file.getName());
			writer.newLine();
			writer.write(String.valueOf(size));
			writer.newLine();
			writer.flush();
			
			int bufSize = 1048576;
			byte[] buf = new byte[bufSize];
			fin = new FileInputStream(file);
			while(size > 0) {
				int len = fin.read(buf, 0, size > bufSize ? bufSize : (int)size);
				out.write(buf, 0, len);
			}
			out.flush();
			
			String ret = reader.readLine();
			if(ret.equals("Done.")) {
				return true;
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if(fin != null) {
				try {
					fin.close();
				} catch (IOException e) {
					e.printStackTrace();
				}				
			}
			if(socket != null) {
				try {
					socket.close();
				} catch (IOException e) {
					e.printStackTrace();
				}				
			}
		}
		
		return false;
	}
	
}
