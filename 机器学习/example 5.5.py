import math
import random
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

def load_data(file_name):
	X, Y = [], []
	data = open(file_name).readlines()
	data = data[1:]
	for line in data:
		line = line.strip().split(',')
		X.append(line[1:-1])
		if line[-1] == '是':
			Y.append(1.0)
		else:
			Y.append(0.0)
	print len(X[0])
	for i in range(len(X[0])):
		if i in [6, 7]:
			for j in range(len(X)):
				X[j][i] = float(X[j][i])
			continue
		id_set = {}
		id_cnt = 1
		for j in range(len(X)):
			if id_set.has_key(X[j][i]):
				X[j][i] = id_set[X[j][i]]
			else:
				id_set[X[j][i]] = 1.0*id_cnt
				X[j][i] = id_set[X[j][i]]
				id_cnt += 1
	return X, Y

class BP:

	def __init__(self):
		self.step_length = 1
		self.Y_dim = 1
		self.X_dim = 8
		self.H_dim = 10
		self.w = [ [random.random() for i in range(self.H_dim)] for j in range(self.Y_dim) ]
		self.v = [ [random.random() for i in range(self.X_dim)] for j in range(self.H_dim) ]
		self.b = [ random.random() for i in range(self.H_dim) ]
		self.theta = [ random.random() for i in range(self.Y_dim) ]
		self.gamma = [ random.random() for i in range(self.H_dim) ]
		self.iter = 0
		self.g = 0.0
		self.e = [ 0 for i in range(self.H_dim) ]
		pass
	
	def train(self, X, Y):
		while(self.eval() == True):
			n = len(Y)
			for i in range(n):
				x, y = X[i], Y[i]
				cur_y = self._output(x)
				self._output_layer_descent(y, cur_y)
				self._hidden_layer_descent()
				self._update(x)
				#print y, cur_y, self.w

	def test(self, x):
		return self._output(x)
		pass
		
	def eval(self):
		self.iter += 1
		if self.iter > 1000:
			return False
		else:
			return True
		pass
		
	def _sigmod(self, x):
		return 1.0 / (1.0 + math.exp(-x))
	
	def _output_layer_descent(self, y, cur_y):
		self.g = cur_y*(1.0-cur_y)*(y-cur_y)
		pass

	def _hidden_layer_descent(self):
		for i in range(self.H_dim):
			self.e[i] = self.b[i]*(1-self.b[i])*self.w[0][i]*self.g
			#b[i] = _sigmod(\sum-gamma)
		pass

	def _output(self, x):
		for i in range(self.H_dim):
			alpha = 0.0
			for j in range(self.X_dim):
				alpha += self.v[i][j]*x[j]
			self.b[i] = self._sigmod(alpha-self.gamma[i])
		beta = 0.0
		for h in range(self.H_dim):
			beta += self.w[0][h]*self.b[h]
		cur_y = self._sigmod(beta-self.theta[0])
		return cur_y
		pass
		
	def _update(self, x):
		for i in range(self.H_dim):
			self.w[0][i] += self.step_length*self.g*self.b[i]
		self.theta[0] += -self.step_length*self.g
		for h in range(self.H_dim):
			for i in range(self.X_dim):
				self.v[h][i] += self.step_length*self.e[h]*x[i]
			self.gamma[h] += -self.step_length*self.e[h]
		
if __name__ == '__main__':
	file_name = 'data3.0.csv'
	X, Y = load_data(file_name)
	#X_train = X[2:-2]
	#Y_train = Y[2:-2]
	#X_test = X[:2] + X[-2:]
	#Y_test = Y[:2] + Y[-2:]
	bp = BP()
	#X = X_train
	#Y = Y_train
	bp.train(X, Y)
	n = len(Y)
	for i in range(len(Y)):
		x = X[i]
		actual_y = Y[i]
		predict_y = bp.test(x)
		print actual_y, predict_y
