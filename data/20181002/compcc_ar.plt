set xlabel "Number of Threads"
set ylabel "Abort Rate"

set format y"%10.3f"
set yrange [0:1]

set lmargin 10
set bmargin 4
set xlabel offset 0,0
set ylabel offset 5,0


set xlabel "Number of threads"
set ylabel "Abort Rate"
set key left top
set terminal postscript eps enhanced color size 9cm,7cm
set output "comp_cicada_silo_ermia_ss2pl_mocc_tictoc_tuple200_r0_ar.eps"
plot "result_cicada_r0_tuple200_ar.dat" w errorlines title "Cicada", "result_silo_r0_tuple200_ar.dat" w errorlines title "Silo", "result_ermia_r0_tuple200_ar.dat" w errorlines title "ERMIA", "result_ss2pl_r0_tuple200_ar.dat" w errorlines title "SS2PL", "result_mocc_r0_tuple200_ar.dat" w errorlines title "MOCC", "result_tictoc_r0_tuple200_ar.dat" w errorlines title "TicToc",

set xlabel "Number of threads"
set ylabel "Abort Rate"
set key left top
set terminal postscript eps enhanced color size 9cm,7cm
set output "comp_cicada_silo_ermia_ss2pl_mocc_tictoc_tuple1k_r0_ar.eps"
plot "result_cicada_r0_tuple1k_ar.dat" w errorlines title "Cicada", "result_silo_r0_tuple1k_ar.dat" w errorlines title "Silo", "result_ermia_r0_tuple1k_ar.dat" w errorlines title "ERMIA", "result_ss2pl_r0_tuple1k_ar.dat" w errorlines title "SS2PL", "result_mocc_r0_tuple1k_ar.dat" w errorlines title "MOCC", "result_tictoc_r0_tuple1k_ar.dat" w errorlines title "TicToc",

set xlabel "Number of threads"
set ylabel "Abort Rate"
set key left top
set terminal postscript eps enhanced color size 9cm,7cm
set output "comp_cicada_silo_ermia_ss2pl_mocc_tictoc_tuple1m_r0_ar.eps"
plot "result_cicada_r0_tuple1m_ar.dat" w errorlines title "Cicada", "result_silo_r0_tuple1m_ar.dat" w errorlines title "Silo", "result_ermia_r0_tuple1m_ar.dat" w errorlines title "ERMIA", "result_ss2pl_r0_tuple1m_ar.dat" w errorlines title "SS2PL", "result_mocc_r0_tuple1m_ar.dat" w errorlines title "MOCC", "result_tictoc_r0_tuple1m_ar.dat" w errorlines title "TicToc",

set xlabel "Number of threads"
set ylabel "Abort Rate"
set key left top
set terminal postscript eps enhanced color size 9cm,7cm
set output "comp_cicada_silo_ermia_ss2pl_mocc_tictoc_tuple200_r2_ar.eps"
plot "result_cicada_r2_tuple200_ar.dat" w errorlines title "Cicada", "result_silo_r2_tuple200_ar.dat" w errorlines title "Silo", "result_ermia_r2_tuple200_ar.dat" w errorlines title "ERMIA", "result_ss2pl_r2_tuple200_ar.dat" w errorlines title "SS2PL", "result_mocc_r2_tuple200_ar.dat" w errorlines title "MOCC", "result_tictoc_r2_tuple200_ar.dat" w errorlines title "TicToc",

set xlabel "Number of threads"
set ylabel "Abort Rate"
set key left top
set terminal postscript eps enhanced color size 9cm,7cm
set output "comp_cicada_silo_ermia_ss2pl_mocc_tictoc_tuple1k_r2_ar.eps"
plot "result_cicada_r2_tuple1k_ar.dat" w errorlines title "Cicada", "result_silo_r2_tuple1k_ar.dat" w errorlines title "Silo", "result_ermia_r2_tuple1k_ar.dat" w errorlines title "ERMIA", "result_ss2pl_r2_tuple1k_ar.dat" w errorlines title "SS2PL", "result_mocc_r2_tuple1k_ar.dat" w errorlines title "MOCC", "result_tictoc_r2_tuple1k_ar.dat" w errorlines title "TicToc",

set xlabel "Number of threads"
set ylabel "Abort Rate"
set key left top
set terminal postscript eps enhanced color size 9cm,7cm
set output "comp_cicada_silo_ermia_ss2pl_mocc_tictoc_tuple1m_r2_ar.eps"
plot "result_cicada_r2_tuple1m_ar.dat" w errorlines title "Cicada", "result_silo_r2_tuple1m_ar.dat" w errorlines title "Silo", "result_ermia_r2_tuple1m_ar.dat" w errorlines title "ERMIA", "result_ss2pl_r2_tuple1m_ar.dat" w errorlines title "SS2PL", "result_mocc_r2_tuple1m_ar.dat" w errorlines title "MOCC", "result_tictoc_r2_tuple1m_ar.dat" w errorlines title "TicToc",

set xlabel "Number of threads"
set ylabel "Abort Rate"
set key left top
set terminal postscript eps enhanced color size 9cm,7cm
set output "comp_cicada_silo_ermia_ss2pl_mocc_tictoc_tuple200_r5_ar.eps"
plot "result_cicada_r5_tuple200_ar.dat" w errorlines title "Cicada", "result_silo_r5_tuple200_ar.dat" w errorlines title "Silo", "result_ermia_r5_tuple200_ar.dat" w errorlines title "ERMIA", "result_ss2pl_r5_tuple200_ar.dat" w errorlines title "SS2PL", "result_mocc_r5_tuple200_ar.dat" w errorlines title "MOCC", "result_tictoc_r5_tuple200_ar.dat" w errorlines title "TicToc",

set xlabel "Number of threads"
set ylabel "Abort Rate"
set key left top
set terminal postscript eps enhanced color size 9cm,7cm
set output "comp_cicada_silo_ermia_ss2pl_mocc_tictoc_tuple1k_r5_ar.eps"
plot "result_cicada_r5_tuple1k_ar.dat" w errorlines title "Cicada", "result_silo_r5_tuple1k_ar.dat" w errorlines title "Silo", "result_ermia_r5_tuple1k_ar.dat" w errorlines title "ERMIA", "result_ss2pl_r5_tuple1k_ar.dat" w errorlines title "SS2PL", "result_mocc_r5_tuple1k_ar.dat" w errorlines title "MOCC", "result_tictoc_r5_tuple1k_ar.dat" w errorlines title "TicToc",

set xlabel "Number of threads"
set ylabel "Abort Rate"
set key left top
set terminal postscript eps enhanced color size 9cm,7cm
set output "comp_cicada_silo_ermia_ss2pl_mocc_tictoc_tuple1m_r5_ar.eps"
plot "result_cicada_r5_tuple1m_ar.dat" w errorlines title "Cicada", "result_silo_r5_tuple1m_ar.dat" w errorlines title "Silo", "result_ermia_r5_tuple1m_ar.dat" w errorlines title "ERMIA", "result_ss2pl_r5_tuple1m_ar.dat" w errorlines title "SS2PL", "result_mocc_r5_tuple1m_ar.dat" w errorlines title "MOCC", "result_tictoc_r5_tuple1m_ar.dat" w errorlines title "TicToc",

set xlabel "Number of threads"
set ylabel "Abort Rate"
set key left top
set terminal postscript eps enhanced color size 9cm,7cm
set output "comp_cicada_silo_ermia_ss2pl_mocc_tictoc_tuple200_r8_ar.eps"
plot "result_cicada_r8_tuple200_ar.dat" w errorlines title "Cicada", "result_silo_r8_tuple200_ar.dat" w errorlines title "Silo", "result_ermia_r8_tuple200_ar.dat" w errorlines title "ERMIA", "result_ss2pl_r8_tuple200_ar.dat" w errorlines title "SS2PL", "result_mocc_r8_tuple200_ar.dat" w errorlines title "MOCC", "result_tictoc_r8_tuple200_ar.dat" w errorlines title "TicToc",

set xlabel "Number of threads"
set ylabel "Abort Rate"
set key left top
set terminal postscript eps enhanced color size 9cm,7cm
set output "comp_cicada_silo_ermia_ss2pl_mocc_tictoc_tuple1k_r8_ar.eps"
plot "result_cicada_r8_tuple1k_ar.dat" w errorlines title "Cicada", "result_silo_r8_tuple1k_ar.dat" w errorlines title "Silo", "result_ermia_r8_tuple1k_ar.dat" w errorlines title "ERMIA", "result_ss2pl_r8_tuple1k_ar.dat" w errorlines title "SS2PL", "result_mocc_r8_tuple1k_ar.dat" w errorlines title "MOCC", "result_tictoc_r8_tuple1k_ar.dat" w errorlines title "TicToc",

set xlabel "Number of threads"
set ylabel "Abort Rate"
set key left top
set terminal postscript eps enhanced color size 9cm,7cm
set output "comp_cicada_silo_ermia_ss2pl_mocc_tictoc_tuple1m_r8_ar.eps"
plot "result_cicada_r8_tuple1m_ar.dat" w errorlines title "Cicada", "result_silo_r8_tuple1m_ar.dat" w errorlines title "Silo", "result_ermia_r8_tuple1m_ar.dat" w errorlines title "ERMIA", "result_ss2pl_r8_tuple1m_ar.dat" w errorlines title "SS2PL", "result_mocc_r8_tuple1m_ar.dat" w errorlines title "MOCC", "result_tictoc_r8_tuple1m_ar.dat" w errorlines title "TicToc",