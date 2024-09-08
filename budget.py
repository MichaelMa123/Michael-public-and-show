class Category:
    ledger =[]
    name=''
    sum_total=0
    def __init__(self,Categ):
        self.name=Categ
        self.sum_total=0
        self.ledger=[]
    
    def deposit(self,amount:int,description:str=''):
        self.ledger.append({'amount': amount, 'description': description})
        self.sum_total+=amount
    
    def withdraw(self,amount:int,description:str=''):
        if self.check_funds(amount):
            self.ledger.append({'amount': -amount, 'description': description})
            self.sum_total-=amount
            return True
        else:
            return False
    
    def get_balance(self):
        return self.sum_total

    def transfer(self,amount,target):
        if self.check_funds(amount):
            self.ledger.append({'amount': -amount, 'description': f'Transfer to {target.name}'})
            target.deposit(amount,f'Transfer from {self.name}')
            self.sum_total-=amount
            return True
        else:
            return False

    def check_funds(self,amount):
        if self.sum_total<amount:
            return False
        else:
            return True

    def __str__(self):
        output=''
        output+=self.name.center(30,'*')
        output+='\n'
        for i in self.ledger:
            description=''
            if len(i['description'])>23:
                j=0
                while j<23:
                    description+=i['description'][j]
                    j+=1
            else:
                description=i['description']
            m=i['amount']
            l=f'{m:0.2f}'
            if len(l)>7:
                q=0
                v=''
                while q<7:
                    v+=l[q]
            else:
                v=l

            k=int(30-len(l))
            output += f"{description:<{23}}{v:>{7}}\n"
        s=f'{self.sum_total:0.2f}'
        output+=f'Total: {s}'
        return output

def create_spend_chart(categories):
    total_spend=0
    spending_per=[]
    spending_percent=[]
    for element in categories:
        spend=0
        for entry in element.ledger:
            if entry['amount']<0:
                total_spend+=-entry['amount']
                spend-=entry['amount']
        spending_per.append(spend)
        print(spending_per)
    count=0 
    for element in  spending_per:
        spending_percent.append(spending_per[count]/total_spend)
        count+=1
    spending_percent[0]+=0
    percent=100
    lists='Percentage spent by category\n'
    while percent>=0:
        lists+=f"{percent:>{3}}|"
        for entry in spending_percent:
            if round(entry*100)>=(percent):
                lists+=' o '
            else:
                lists+='   '
        lists+=' \n'
        percent-=10
    lists+='    '
    for k in categories:
        lists+='---'
    lists+='-\n'
    length=[]
    length=[len(i.name)for i in categories]
    longest=max(length)
    longest_name_length = max(len(category.name) for category in categories)

    # Loop through each letter position and print vertically
    for i in range(longest_name_length):
        lists += '    '  # Indentation for the vertical names
        for category in categories:
            if i < len(category.name):
                lists += f" {category.name[i]} "
            else:
                lists += '   '  
        # Fill in with spaces if name is shorter'
        if i==longest_name_length-1:
            lists +=' '
        else: 
            lists += ' \n'
    print(total_spend)
    return lists
