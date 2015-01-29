var cheerio = require('cheerio')
var fs = require('fs')

fs.readFile('email.html', 'utf8', function(err, data) {
    if (err) throw err;

    $ = cheerio.load(data, { normalizeWhiteSpace: true });

    var date = $('#Anada1_date td').text();
    var flight = $('#Anada1_flight').text().trim();

    var dep = [];
    $('#Anada1_departurestation td').each(function(i, elem) {
        dep[i] = $(this).text().trim();
    });

    var arr = [];
    $('#Anada1_1arrivalstation td').each(function(i, elem) {
        arr[i] = $(this).text().trim();
    });

    console.log("Date: " + date);
    console.log("Flight: " + flight);
    console.log("Departure Location: " + dep[0]);
    console.log("Departure Gate: " + dep[1]);
    console.log("Departure Time: " + dep[2]);
    console.log("Arrival Location: " + arr[0]);
    console.log("Arrival Gate: " + arr[1]);
    console.log("Arrival Time: " + arr[2]);

    var inTable = $('.tableInsideBorder table').first();
    var con = inTable.find('td').last().text().trim();

    console.log("Confirmation Number: " + con);
});

