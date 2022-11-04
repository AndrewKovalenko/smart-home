const url = 'https://aviationweather.gov/cgi-bin/json/MetarJSON.php?zoom=9&filter=prior&density=1&taf=0&bbox=-124.57,46.96,-120.14,48.8';
const stations = [
"KEAT",
"KELN",
"KSMP",
"KPLU",
"KRNT",
"KBFI",
"KSEA",
"KTIW",
"KTCM",
"KGRF",
"KPWT",
"KOLM",
"KSHN",
"KHQM",
"KUIL",
"KCLM",
"CYYJ",
"KFHR",
"KORS",
"KBLI",
"KBVS",
"KNUW",
"K0S9",
"KPAE",
"KAWO",
"KS52"];

//KBLI

//KUIL KS52

//KHQM

async function main() {
  const weatherResponse = await fetch(url);
  const weatherData = await weatherResponse.json();
  const weatherStations = weatherData.features.reduce((metars, record) => {
    if(typeof record.properties.id !== 'undefined') {
      return [...metars, record];
    }

    return metars;
  }, []);

  const missignStations = stations.reduce((missing, station) => {
    const weatherReport = weatherStations.find(
      metar => metar.properties.id === station
    );

    if(!weatherReport) {
      return [...missing, station];
    }

    return missing;
  }, []);


  console.log(`Total stations: ${weatherStations.length}`);
  console.dir(weatherStations);

  console.log('Missing stations');
  console.dir(missignStations);
}

main();