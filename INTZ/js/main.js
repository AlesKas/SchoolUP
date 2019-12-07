$(function(){
    $(document).ready(function(){
        updateTime();
    })

    var intretval = setInterval(updateTime, 100);
    
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

    var modal = document.getElementById('myModal');
    var img = document.getElementById('myImg');
    var modalImg = document.getElementById("img01");
    var captionText = document.getElementById("caption");
    
    img.onclick = function(){
    modal.style.display = "block";
    modalImg.src = this.src;
    captionText.innerHTML = this.alt;
    }

    var span = document.getElementsByClassName("close")[0];

    span.onclick = function() { 
    modal.style.display = "none";
    }

})