using Meisters.Models;
using Meisters.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Meisters.Data
{
    public class TablesData : Observable
    {
        private Table[] _tables = new Table[24];

        public Table[] Tables
        {
            get => _tables;
            set
            {
                _tables = value;
                RaiseTablesPropertyChanged();
            }
        }

        public void RaiseTablesPropertyChanged()
        {
            OnPropertyChanged(nameof(Tables));
        }
    }
}
