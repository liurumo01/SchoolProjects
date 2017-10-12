<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.io.File" %>
<%@ page import="java.io.FilenameFilter" %>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.HashMap" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>

	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
		<title>视频列表</title>
		<link rel="stylesheet" href="${pageContext.request.contextPath}/main.css"/>
		<script type="text/javascript" src="${pageContext.request.contextPath}/jquery-3.2.1.js"></script>
		<script type="text/javascript">
			$(".play").bind("click", function() {
					window.open("${pageContext.request.contextPath}/player.jsp?id=" + $(this).attr("value"));
			});
			window.onload = function() {
				var tags = document.getElementsByClassName("play");
				for(var i in tags) {
					tags[i].onclick = function() {
						window.open("${pageContext.request.contextPath}/player.jsp?id=" + this.value);
					}
				}
			}
			/*
			$(function() {
				$(".play").bind("click", function() {
					window.open("${pageContext.request.contextPath}/player.jsp?id=" + $(this).attr("value"));
				});
			});
			*/
		</script>
	</head>
	
	<%
		String videoPath = (String) application.getAttribute("video-path");
		File dir = new File(videoPath);
		final Map<Integer, String> map = new HashMap<Integer, String>();
		if(dir.exists()) {
			File[] videos = dir.listFiles(new FilenameFilter() {
				private Integer index = 1;
				@Override
				public boolean accept(File dir, String name) {
					if(name.endsWith(".mp4")) {
						map.put(index, name);
						index++;
						return true;
					}
					return false;
				}
			});
			request.setAttribute("videos", videos);
			application.setAttribute("map", map);
		}
	%>
	
	<body>
		
		<h1>视频列表</h1>
		
		<br><br>
		
		<table class="grid">
			<tr>
				<td>序号</td>
				<td>文件名</td>
			</tr>
			<c:set var="index" value="1"></c:set>
			<c:forEach items="${videos}" var="video">
				<tr>
					<td>${index}</td>
					<td><a class="play" value="${index}">${video.name}</a></td>
				</tr>
				<c:set var="index" value="${index + 1}"></c:set>
			</c:forEach>
		</table>
		
	</body>
	
</html>