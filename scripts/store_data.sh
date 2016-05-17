#!/bin/bash
HEJ=$(tdtool -l | grep '90' | grep '1A2D' | cut -f 5 | tr -d '%')
if [ -n "$HEJ" ]; then
	mysql -u dlxflwpwr -pdlxflwpwr << EOF
	use dlxflwpwr;
	insert into data (data) values($HEJ);
	exit
EOF
fi
