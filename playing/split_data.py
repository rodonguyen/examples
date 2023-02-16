#%%
import pandas



filepath = '../data/mnist_train_2000.csv'
df = pandas.read_csv(filepath, header=None)
length = len(df)



def split(split_num):
   start_index = 0
   each_split_length = length // split_num

   for i in range(split_num):

      # Last split
      if i == split_num:
         # Spliting
         df_split = df.copy()[start_index : start_index + each_split_length]
         # Save in csv
         save_path = f'../data/mnist_train_2000_{split_num}_{(i+1):03d}.csv'
         df_split.to_csv(save_path)
         break

      # For all other splits
      df_split = df.copy()[start_index : start_index + each_split_length]
      # Save in csv
      save_path = f'../data/mnist_train_2000_{split_num}_{(i+1):03d}.csv'
      df_split.to_csv(save_path, header=None, index=None)

      # print(start_index, start_index+each_split_length)
      start_index += each_split_length

for i in range(2,101,2):
   split(i)
#%%
