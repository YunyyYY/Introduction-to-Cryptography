% for shift = 1:26
%     disp(char(mod(abs('EVIRE') - abs('A') - shift, 26) + 'a'))
%     disp(shift)
% end

plain = abs('dont') - abs('a');
cypher = abs('ELNI') - abs('A');
plain = reshape(plain, 2, 2)';
cypher = reshape(cypher, 2, 2)';

% key =  plain \ cypher;
% key = mod(key * abs(det(plain)), 26)