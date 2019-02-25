vsim -gui work.top

log -r /*

add wave -position insertpoint  \
sim:/top/clock \
sim:/top/reset \
sim:/top/start \
sim:/top/finish \
sim:/top/stdin_rdy \
sim:/top/stdin_ack \
sim:/top/stdin_data \
sim:/top/stdout_data \
sim:/top/stdout_rdy \
sim:/top/stdout_ack
force -freeze sim:/top/clock 1 0, 0 {50 ps} -r 100
force -freeze sim:/top/reset 0 0
force -freeze sim:/top/start 1 0
force -freeze sim:/top/stdin_ack 1 0
force -freeze sim:/top/stdin_data 10101111101011010111110101111111 0
force -freeze sim:/top/stdout_ack 1 0

run -all