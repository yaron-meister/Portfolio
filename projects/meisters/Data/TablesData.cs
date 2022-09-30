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
        // 24 tables + 1 general extra for administrations
        private Table[] _tables = new Table[25];
        private Table _currentTable;
        private bool _isReservationOpen = false;

        public Table[] Tables
        {
            get => _tables;
            set
            {
                _tables = value;
                OnPropertyChanged();
            }
        }

        public Table CurrentTable
        {
            get => _currentTable;
            set
            {
                _currentTable = value;
                OnPropertyChanged();
            }
        }

        public bool IsReservationOpen
        {
            get => _isReservationOpen;
            set
            {
                _isReservationOpen = value;
                OnPropertyChanged();
            }
        }

        public void RaiseTablesPropertyChanged()
        {
            OnPropertyChanged(nameof(Tables));
        }
    }
}
