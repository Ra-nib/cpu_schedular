// Ensure to serve this file using a local server, e.g., python -m http.server 8000

d3.json("scheduling_results.json").then(data => {
    if (data.fcfs) {
        renderAlgorithmResults("FCFS Scheduling", data.fcfs);
    }
    if (data.sjn) {
        renderAlgorithmResults("SJN Scheduling", data.sjn);
    }
    if (data.round_robin) {
        renderAlgorithmResults(`Round Robin Scheduling (Quantum = ${data.round_robin.quantum})`, data.round_robin);
    }
    if (data.priority) {
        renderAlgorithmResults("Priority Scheduling", data.priority);
    }
}).catch(error => {
    console.error("Error loading the JSON file:", error);
});

function renderAlgorithmResults(title, data) {
    const chartDiv = d3.select("#chart");

    chartDiv.append("h2").text(title);

    renderGanttChart(chartDiv, data.schedule);
    renderMetrics(chartDiv, data);
    chartDiv.append("hr"); // Add a horizontal line between different algorithms
}

function renderGanttChart(parentDiv, schedule) {
    const svg = parentDiv.append("svg")
        .attr("width", 800)
        .attr("height", 100);

    const barHeight = 20;

    const bars = svg.selectAll(".bar")
        .data(schedule)
        .enter()
        .append("g")
        .attr("transform", (d, i) => `translate(${i * barHeight * 2}, 0)`);

    bars.append("rect")
        .attr("class", "bar")
        .attr("width", barHeight * 2)
        .attr("height", barHeight);

    bars.append("text")
        .attr("x", barHeight)
        .attr("y", barHeight / 2)
        .attr("dy", ".35em")
        .text(d => d);
}

function renderMetrics(parentDiv, metrics) {
    const metricsDiv = parentDiv.append("div").attr("class", "metrics");

    metricsDiv.append("p").text(`Average Waiting Time: ${metrics.avg_waiting_time}`);
    metricsDiv.append("p").text(`Average Turnaround Time: ${metrics.avg_turnaround_time}`);
    metricsDiv.append("p").text(`CPU Utilization: ${metrics.cpu_utilization}%`);
    metricsDiv.append("p").text(`Throughput: ${metrics.throughput} processes/unit time`);
}

