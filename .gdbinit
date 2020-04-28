define target remote
target extended-remote $arg0
end

define target hookpost-remote
monitor swdp_scan
attach 1
load
b main
end



