<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
    <head>
        <base href="<%=basePath%>">
        <title>Database Connection Testing</title>
        <link rel="stylesheet" type="text/css" href="css/current.css">
        <script type="text/javascript" src="js/jquery-3.2.1.js"></script>
        <script type="text/javascript">
            $(document).ready(function () {
                var operate = "${requestScope.operate}";
                var tables = [];
                var isNullable = [];
                var m, n;
                //上移动画
                if (operate!="") $(".header").animate({"padding-top":'15vh'});

                // 获得每个表的信息，将其存在js变量内
                <c:if test="${not empty requestScope.tables}">
                    <c:forEach items="${requestScope.tables}" var="table" varStatus="m">
                        m = ${m.count};
                        tables[m-1] = [];
                        isNullable[m-1] = [];

                        // 设置每个表的字段名
                        <c:forEach items="${table.colName}" var="column" varStatus="n">
                            n = ${n.count};
                            tables[m-1][n-1] = "${column}";
                        </c:forEach>

                        // 设置每个字段是否为空
                        <c:forEach items="${table.isColumnsNullable}" var="isNullable" varStatus="n">
                            n = ${n.count};
                            isNullable[m-1][n-1]="${isNullable}";
                        </c:forEach>
                    </c:forEach>
                    if (operate =="insertData") $("input[name='colNum']").val(tables[0].length);
                </c:if>

                //change column list
                $("select[name='table-name']").change(function () {
                    var select_col = $("select[name='column-name']");
                    select_col.html("");
                    var index = $(this).children("option:selected").attr("name");
                    for (var i=1; i<=tables[index-1].length; i++){
                        select_col.append("<option value=" + tables[index-1][i-1] + ">" + tables[index-1][i-1] + "</option>");
                    }
                });

                //change input area
                $(".insert_input>select").change(function () {
                    var col_area = $(".col-area");
                    var divNum = $(".insert_input").children(".col-area").length;
                    // 删除多余的行，只保留一行
                    for (var j=0; j < divNum-1; j++){
                        deleteRow();
                    }
                    // 删除所有输入框
                    col_area.html("");
                    // 重新添加改变的新表的字段输入框
                    var index = $(this).children("option:selected").attr("name");
                    for (var i=1; i<=tables[index-1].length; i++){
                        col_area.append("<span></span>");
                        var span = $(".col-area>span:nth-child("+i+")");
                        span.append("<label>"+tables[index-1][i-1]+"</label>");
                        if (isNullable[index-1][i-1] == "1"){
                            span.append("<input type=\"text\" name=\"col-value\" size=\"15px\" placeholder=\"可为空\">");
                        }
                        else {
                            span.append("<input type=\"text\" name=\"col-value\" size=\"15px\" placeholder=\"不可为空\">");
                        }
                    }
                    // 设置改变表名后的字段数
                    $("input[name='colNum']").val(getColNum());
                });


                /*
                //show corresponding table when click delete and update button
                $(".input:eq(3)>select[name='table-name'],.input:eq(2)>select[name='table-name']").change(function () {
                    // 获得类型
                    // var operateType = $(this).nextAll("button").val();


                    $.ajax({
                        type:"GET",
                        url:"/DBServlet",
                        data:{selected_table:$(this).val()},
                        statusCode: {404: function() {
                                alert('page not found'); }
                        },
                        success:function(data,textStatus){
                            $("#sp").html(data);
                        }
                    });
                });
                */

            });

            function addRow(){
                var div = "<div class=\"col-area\">" + $(".col-area").html() + "</div>";
                $("button#add").before(div);
            }
            function deleteRow(){
                if ($(".insert_input").children(".col-area").length == 1) alert("无法删除第一行！");
                else {
                    $("div.col-area:last").remove();
                }
            }
            function getColNum() {
                return $('div.col-area').children('span').length;
            }

        </script>
    </head>
    <body>
        <div class="header">
            <h1>Database Connection</h1>
            <div class="block wrap">
                <form action="/DBServlet" method="get">
                    <button type="submit" name="type" value="query">查询数据</button>
                    <button type="submit" name="type" value="insertData">插入数据</button>
                    <button type="submit" name="type" value="updateData">更新数据</button>
                    <button type="submit" name="type" value="deleteData">删除数据</button>
                </form>
            </div>
        </div>
        <c:if test="${not empty requestScope.tables}">
            <div class="block content">
                <form action="/DBResultServlet" method="post">

                    <c:if test="${requestScope.operate == \"query\"}">
                        <div class="input query_input">
                            <h3>查询条件</h3>

                            <select name="table-name">
                                <c:forEach items="${requestScope.tables}" var="table" varStatus="i">
                                    <option name="${i.count}" value="${table.tableName}">${table.tableName}</option>
                                </c:forEach>
                            </select>

                            <select name="column-name">
                                <c:forEach items="${requestScope.tables[0].colName}" var="column" varStatus="i">
                                    <option value="${column}">${column}</option>
                                </c:forEach>
                            </select>

                            <input type="text" name="col-value" size="40px" placeholder="输入字段搜索值(为空则显示全表)">
                            <button class="dark" type="submit" name="type" value="query">查询</button>
                        </div>
                    </c:if>

                    <c:if test="${requestScope.operate == \"insertData\"}">
                        <div class="input insert_input">
                            <h3>插入数据</h3>
                            <select name="table-name">
                                <c:forEach items="${requestScope.tables}" var="table" varStatus="i">
                                    <option name="${i.count}" value="${table.tableName}">${table.tableName}</option>
                                </c:forEach>
                            </select>
                            <div class="col-area">
                                <c:forEach items="${requestScope.tables[0].colName}" var="column" varStatus="i">
                                    <span>
                                        <label>${column}</label>
                                        <c:choose>
                                            <c:when test="${requestScope.tables[0].isColumnsNullable[i.count-1] == 1}">
                                                <input type="text" name="col-value" size="15px" placeholder="可为空">
                                            </c:when>
                                            <c:otherwise>
                                                <input type="text" name="col-value" size="15px" placeholder="不可为空">
                                            </c:otherwise>
                                        </c:choose>
                                    </span>
                                </c:forEach>
                            </div>
                            <button id="add" type="button" class="dark" onclick="addRow()">增加一行</button>&nbsp;&nbsp;
                            <button id="delete"  type="button" class="dark" onclick="deleteRow()">删除一行</button>&nbsp;&nbsp;
                            <button class="darkd" type="submit" name="type" value="insertData">插入</button>
                            <input type="text" style="display: none" name="colNum">
                        </div>
                    </c:if>

                    <c:if test="${requestScope.operate == \"updateData\"}">
                        <div class="input update_input">
                            <h3>更新数据</h3>

                            <select name="table-name">
                                <c:forEach items="${requestScope.tables}" var="table" varStatus="i">
                                    <option name="${i.count}" value="${table.tableName}">${table.tableName}</option>
                                </c:forEach>
                            </select>

                            <select name="column-name">
                                <c:forEach items="${requestScope.tables[0].colName}" var="column" varStatus="i">
                                    <option value="${column}">${column}</option>
                                </c:forEach>
                            </select>
                            <input name="col-value" type="text" size="30px" placeholder="输入查找字段值">

                            <select name="column-name">
                                <c:forEach items="${requestScope.tables[0].colName}" var="column" varStatus="i">
                                    <option value="${column}">${column}</option>
                                </c:forEach>
                            </select>

                            <input name="col-value" type="text" size="30px" placeholder="输入更新字段值">
                            <button class="dark" type="submit" name="type" value="updateData">更新</button>
                        </div>
                    </c:if>

                    <c:if test="${requestScope.operate == \"deleteData\"}">
                        <div class="input delete_input">
                            <h3>删除数据</h3>

                            <select name="table-name">
                                <c:forEach items="${requestScope.tables}" var="table" varStatus="i">
                                    <option name="${i.count}" value="${table.tableName}">${table.tableName}</option>
                                </c:forEach>
                            </select>

                            <select name="column-name">
                                <c:forEach items="${requestScope.tables[0].colName}" var="column" varStatus="i">
                                    <option value="${column}">${column}</option>
                                </c:forEach>
                            </select>

                            <input name="col-value" type="text" size="40px" placeholder="输入需要删除的记录对应字段值">
                            <button class="dark" type="submit" name="type" value="deleteData">删除</button>
                        </div>
                    </c:if>

                </form>
            </div>
        </c:if>
    </body>
</html>
