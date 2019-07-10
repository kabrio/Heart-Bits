# Welcome to Sonic Pi v3.1
sleepTimes = [2.0, 2.0].ring
/Pachelbel/
chords = [(chord :C, :major7), (chord :G, :major7), (chord :A, :minor), (chord :E, :minor), (chord :F, :major), (chord :C, :major), (chord :F, :major), (chord :G, :major)].ring
i = 0;
inputVal = [0]


live_loop :foo do
  use_real_time
  sleepTime = 2.0
  /play chords.tick, release: sleepTime/
  print(inputVal)
  use_osc "192.168.0.45", 12000
  osc "/hello/world"
  use_synth :prophet
  play chords[i], release: sleepTime, amp: 1.0, cutoff: 70+(6*inputVal[0])
  if i >= 4
    sleep 2
  else
    sleep 1
  end
  i = i + 1
  if i >= 8
    i = 0
  end
end

in_thread do
  loop do
    inputVal = sync "/osc/control/chords"
    print("hi")
    print(inputVal)
    sleep 0.1
  end
end
