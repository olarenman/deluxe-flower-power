google.charts.load('current', {'packages':['corechart']});
google.charts.setOnLoadCallback(drawChart);

function drawChart() {
    
    var jsonData = $.ajax({
	url: "getData.php",
	dataType: "json",
	async: false}).responseText;

    jsonData = JSON.parse(jsonData);

    var data = new google.visualization.DataTable();

    data.addColumn('datetime', 'Tid');
    data.addColumn('number', 'Fuktighet (%)');
    
    for(var i = 0; i < jsonData.length; i++) {
	var t = jsonData[i].time.split(/[- :]/);
	var date = new Date(t[0], t[1]-1, t[2], t[3], t[4], t[5]);
	data.addRow([date, jsonData[i].data]);
    }

    var options = {
        title: 'Dlxflwpwr',
	curveType: 'function',
	legend: { position: 'bottom' },
	hAxis: { format: 'dd/MM/yyyy HH:mm',
		 slantedText : 'true',
		 textStyle: {fontSize: 12}
	       }	
    };

    var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));
    chart.draw(data, options);
}
