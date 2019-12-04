$(function(){
    $(document).ready(function(){
        updateTime();
    })

    var intretval = setInterval(updateTime, 100);
    console.log("ready")
    function updateTime(){
        var now = new Date(Date.now());
        var hour = now.getHours();
        var minutes = now.getMinutes();

        $("#time").html(relativeTime(hour) + ":" + relativeTime(minutes));
    }

    function relativeTime(time){
        if (time < "10")
        {
            return "0" + time;
        }
        return time;
    }
})