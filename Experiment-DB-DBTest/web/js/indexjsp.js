$(document).ready(function () {
    var operate = "${requestScope.operate}";

    switch (operate){
        case "query":
            $(".query_input").css("display","inline-block");
            break;
        case "insertData":
            $(".insert_input").css("display","inline-block");
            break;
        case "updateData":
            $(".update_input").css("display","inline-block");
            break;
        case "deleteData":
            $(".delete_input").css("display","inline-block");
            break;
    }

    $("select[name='table-name']").change(function () {
        var select_col = $("select[name='column-name']");
        select_col.html("");
        var index = $(this).val();
        /*$.get('',function(){

        },'json');*/

    });

});
