onerror {resume}
quietly set dataset_list [list sim vsim]
if {[catch {datasetcheck $dataset_list}]} {abort}
quietly WaveActivateNextPane {} 0
add wave -noupdate sim:/top/clock
add wave -noupdate sim:/top/reset
add wave -noupdate sim:/top/start
add wave -noupdate sim:/top/finish
add wave -noupdate sim:/top/stdin_rdy
add wave -noupdate sim:/top/stdin_ack
add wave -noupdate sim:/top/stdin_data
add wave -noupdate sim:/top/stdout_data
add wave -noupdate sim:/top/stdout_rdy
add wave -noupdate sim:/top/stdout_ack
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ps} 0}
quietly wave cursor active 0
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
WaveRestoreZoom {27368900 ps} {43752900 ps}
