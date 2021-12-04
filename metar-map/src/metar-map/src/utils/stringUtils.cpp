void split(String response, char separator, String (&responseLines)[])
{
  const uint responseSize = response.length();

  uint from = 0;
  uint8_t stringCounter = 0;

  for (uint i=0; i<responseSize; i++)
  {
    if (response[i] == separator || i == responseSize - 1) {
      String responseLine = response.substring(from, i);
      responseLines[stringCounter] = responseLine;
      from = i + 1;
      stringCounter++;
    }
  }
}