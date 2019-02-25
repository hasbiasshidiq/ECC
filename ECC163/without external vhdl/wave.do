onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /top/clock
add wave -noupdate /top/reset
add wave -noupdate /top/start
add wave -noupdate /top/stdout_rdy
add wave -noupdate /top/stdout_ack
add wave -noupdate /top/stdout_data
add wave -noupdate /top/finish
add wave -noupdate /top/stdin_ack
add wave -noupdate /top/stdin_rdy
add wave -noupdate /top/stdin_data
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {212636489 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 150
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ps
update
WaveRestoreZoom {201976360 ps} {229954886 ps}
