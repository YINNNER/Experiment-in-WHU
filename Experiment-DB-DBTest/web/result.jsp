<%--
  Created by IntelliJ IDEA.
  User: yiner
  Date: 2018/5/21
  Time: 17:29
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" import="java.util.*" pageEncoding="utf-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<html>
<head>
    <title>Result</title>
    <link rel="stylesheet" type="text/css" href="css/current.css">
    <link rel="stylesheet" type="text/css" href="css/result.css">
    <script type="text/javascript" src="js/jquery-3.2.1.js"></script>
    <script type="text/javascript">
        $(document).ready(function () {
            var result = "${requestScope.result}";
            if ((result!="") && (result!="[]")) $(".header").animate({"padding-top":'5vh'});
        });
    </script>
</head>
<body>
    <div class="header"><h1>Operation Result</h1></div>
    <div class="block content">
        <h2 style="margin-top: 0;">${requestScope.status}</h2>
        <c:if test="${not empty requestScope.error}">
            <p>${requestScope.error}</p>
        </c:if>
        <c:if test="${not empty requestScope.result}">
            <table class="table_style" border="1">
                <caption>${requestScope.tableName}</caption>
                <thead>
                    <tr>
                        <c:forEach items="${requestScope.columnNames}" var="colName">
                            <th>${colName}</th>
                        </c:forEach>
                    </tr>
                </thead>
                <tbody>
                    <c:forEach items="${requestScope.result}" var="item" varStatus="i">
                        <tr>
                            <c:forTokens items="${item}" delims="," var="col" varStatus="j">
                                <td>${col}</td>
                            </c:forTokens>
                        </tr>
                    </c:forEach>
                </tbody>
            </table>
        </c:if>
        <button class="dark" onclick="location='index.jsp' ">返回</button>
    </div>

</body>
</html>
