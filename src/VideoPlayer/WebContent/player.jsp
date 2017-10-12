<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.io.File" %>
<%@ page import="java.util.Map" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html>

	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
		<title>视频播放页</title>
		<link rel="stylesheet" href="${pageContext.request.contextPath}/main.css"/>
		<script type="text/javascript" src="${pageContext.request.contextPath}/jquery-3.2.1.js"></script>
	</head>
	
	<%
		String videoPath = (String) application.getAttribute("video-path");
		File dir = new File(videoPath);
		@SuppressWarnings("unchecked")
		final Map<Integer, String> map = (Map<Integer, String>) application.getAttribute("map");
		int id = Integer.parseInt(request.getParameter("id"));
		request.setAttribute("name", map.get(id));
	%>
	
	<body>
		
		<h1>${name}</h1>
		
		<br><br>
		
		<video controls="controls">
			<source src="/videos/${name}" type="video/mp4">
		</video>
		
	</body>
	
</html>