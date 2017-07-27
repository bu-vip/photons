txt = fileread("/home/natalia/Desktop/first_testbed_trails/empty_room/lights_off/lights_off_empty_room1.txt")

tail = 40;
str_sensor_ids = txt(1,1:tail);
sensor_ids = strread(str_sensor_ids, '%s');
sensor_ids = sensor_ids.'
txt = txt(1,tail:end);

values_block_length = 170;
str_values_block = txt(1,1:values_block_length);

block_tail = 7;
str_values_block_id = str_values_block(1:block_tail);

block_ids = strread(str_values_block_id, '%s')

str_values_block = str_values_block(block_tail:end);
values_block = strread(str_values_block, '%d');
values_block = reshape(values_block, [9 4]);
values_block = values_block.'

values_block_length = 170;
str_values_block = txt(1,1:values_block_length)
tail = tail + values_block_length;
txt = txt(1,tail:end);




