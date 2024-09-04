class packet:
  def __init__(self, buffer:list) -> None:
    self._raw_buff = buffer
    self._size = len(buffer)
    self.processed = []

  def verify(self) -> bool:
    if self._size != 1980:
      return False
    for i in range(90):
        if self._raw_buff[22*i] != 'fa':
          print(self._raw_buff[22*i])
          return False
    return True

  def process(self):
    for i in range(90):
      _sample = self._raw_buff[22*i:22*i+22]

      _glob_angle  = int(_sample[1],16)-160
      _rpm = float(int(_sample[2],16) | (int(_sample[3],16) << 8)) / 64.0

      for i in range(4):
        angle = _glob_angle + i
        dist = int(_sample[4+4*i],16) | (int(_sample[5+4*i],16) << 8)
      # _distance = int(_sample[4],16) | (int(_sample[5],16) << 8)

        self.processed.append({"angle": angle, "distance": dist})